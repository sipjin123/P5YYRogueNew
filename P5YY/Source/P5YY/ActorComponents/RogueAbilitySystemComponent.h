// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RogueAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API URogueAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	TMap<int32, FTimerHandle> AbilityCooldownTimers;
	UFUNCTION(BlueprintCallable)
	void RegisterComboTag(int32 ComboSection);
	UFUNCTION()
	void CloseComboWindow(int32 CooldownId);
};
