// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RogueAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayAbilityActivated, FString, ability, float, cooldown);

/**
 * 
 */
UCLASS()
class P5YY_API URogueAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//TMap<int32, FTimerHandle> AbilityCooldownTimers;
	UFUNCTION(BlueprintCallable)
	void RegisterComboTagOld(int32 ComboSection);
	UFUNCTION()
	void CloseComboWindowOld(int32 CooldownId);


public:
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities);
	void AddCharacterAbility(TSubclassOf<UGameplayAbility> EquipAbility, FGameplayTag inputTag);
	void RemoveCharacterAbility(const TSubclassOf<UGameplayAbility> abilityToRemove);
	void RemoveCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> abilitiesToRemove);

	// Activate ability using event to allow custom parameters such as direction
	void TryActivateAbilityUsingEvent(const FGameplayTag& InputTag);

	UPROPERTY(BlueprintAssignable)
	FOnGameplayAbilityActivated OnGameplayAbilityActivated;
	
	// Activate ability using event to allow custom parameters
	UFUNCTION(BlueprintCallable)
	void TryActivateAbilityUsingEventDirection(const FVector OriginLoc, const FVector Direction, const FGameplayTag& TagUsed);
	
	// TODO(BURLIN): Prototype Combo System Coordinate with Jiro regarding placement
	TMap<int32, FTimerHandle> AbilityCooldownTimers;
	UFUNCTION(BlueprintCallable)
	void RegisterComboTag(int32 ComboSection);
	UFUNCTION(BlueprintCallable)
	void CloseComboWindow(int32 CooldownId);
	UPROPERTY(BlueprintReadWrite)
	bool ShowComboLogs = false;
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerRegisterLastInputDirectionFromClient(FVector InputDirection);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void ServerRegisterInputDirectionFromClient(FVector InputDirection);

	UPROPERTY(Replicated, BlueprintReadOnly)
	FVector LastClientInputDirection;

	// Custom code removing tags within a category
	UFUNCTION(BlueprintCallable)
	void RemoveTagsInCategory(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag ParentTag);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_NotifyTagsRemoved(UAbilitySystemComponent* AbilitySystemComponent, const TArray<FGameplayTag>& TagsToRemove);

	// Custom code removing tags within a category
	UFUNCTION(BlueprintCallable)
	void RemoveSpecificTag(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag Tag);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_NotifyTagRemoved(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag TagToRemove);
	
	void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability) override;
};

