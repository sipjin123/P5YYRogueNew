// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERogueAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Interact,
	Attack,
	Defensive,
	Dash,
	Power,
	Special,
	Ultimate,
    MAX UMETA(Hidden)
};

struct RogueData
{
	
};
