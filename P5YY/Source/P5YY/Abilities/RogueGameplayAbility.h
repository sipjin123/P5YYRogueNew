// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "P5YY/Core/RogueData.h"
#include "RogueGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API URogueGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	URogueGameplayAbility();

	// Abilities will activate upon input press
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Abilities")
	ERogueAbilityInputID AbilityInputId;
};
