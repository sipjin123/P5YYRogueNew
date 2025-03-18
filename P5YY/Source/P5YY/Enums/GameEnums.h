// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFactionType : uint8 {
	Neutral = 0 UMETA(DisplayName = "None"),
	Allies = 1 UMETA(DisplayName = "Allies"),
	Mechs = 2 UMETA(DisplayName = "Mechs"),
	Ancients = 3 UMETA(DisplayName = "Ancients"),
	Wildings = 4 UMETA(DisplayName = "Wildings")
};

UENUM(BlueprintType)
enum class ECombatType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Melee = 1 UMETA(DisplayName = "Melee"),
	Ranged = 2 UMETA(DisplayName = "Ranged"),
	Mage = 3 UMETA(DisplayName = "Mage"),
	Healer = 4 UMETA(DisplayName = "Healer")
};

UENUM(BlueprintType)
enum class EMovementType : uint8 {
	None = 0,
	Walking = 1,
	Jogging = 2,
	Running = 3,
	Flying = 3
};

UENUM(BlueprintType)
enum class EEnemyType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Melee1 = 1 UMETA(DisplayName = "Droid"),
	Ranged1 = 2 UMETA(DisplayName = "ScoutDroid"),
	Mage1 = 3 UMETA(DisplayName = "Magus"),
	Healer1 = 4  UMETA(DisplayName = "Willow")
};

UENUM(BlueprintType)
enum class ECollisionType : uint8 {
	Ignore = 0 UMETA(DisplayName = "Ignore"),
	Process = 1 UMETA(DisplayName = "Process"),
	Destroy = 2 UMETA(DisplayName = "Destroy"),
};

UENUM(BlueprintType)
enum class EDebugMsgType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Combat = 1 UMETA(DisplayName = "Combat"),
	Projectile = 2 UMETA(DisplayName = "Projectile"),
	AI = 3 UMETA(DisplayName = "AI"),
	Enemy = 4 UMETA(DisplayName = "Enemy"),
	Ally = 5 UMETA(DisplayName = "Ally"),
	Miner = 6 UMETA(DisplayName = "Miner"),
	Test = 7 UMETA(DisplayName = "Test"),
};

UENUM(BlueprintType)
enum class EDebugColor : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Blue = 1,
	Red = 2,
	Green = 3,
	Yellow = 4,
	Cyan = 5,
	Black = 6
};

class P5YY_API GameEnums
{
public:
	GameEnums();
	~GameEnums();
};
