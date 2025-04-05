// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAbilitySystemComponent.h"


void URogueAbilitySystemComponent::RegisterComboTag(int32 ComboSection)
{
	const int32 Step = ComboSection;
	const FString ComboWindowText = "Combo.Window";
	const FString ComboWindowResult = ComboWindowText + FString::FromInt(Step);

	if (GetOwner()->HasAuthority())
	UE_LOG(LogTemp, Error, TEXT("== %s"), *ComboWindowResult);
	
	// During Notify or montage end
	AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(*ComboWindowResult));


	FTimerHandle& CooldownHandle = AbilityCooldownTimers.FindOrAdd(ComboSection);
	FTimerDelegate CooldownFinishedDelegate;
	CooldownFinishedDelegate.BindUFunction(this, FName("CloseComboWindow"), ComboSection);
	
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, CooldownFinishedDelegate, 3, false);
}

void URogueAbilitySystemComponent::CloseComboWindow(int32 CooldownId)
{
	const FString ComboWindowText = "Combo.Window";
	const FString ComboWindowResult = ComboWindowText + FString::FromInt(CooldownId);

	if (GetOwner()->HasAuthority())
	UE_LOG(LogTemp, Log, TEXT("Cooldown finished for ability: %d -- %s"), CooldownId, *ComboWindowResult);

	RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(*ComboWindowResult));
	AbilityCooldownTimers.Remove(CooldownId);
}