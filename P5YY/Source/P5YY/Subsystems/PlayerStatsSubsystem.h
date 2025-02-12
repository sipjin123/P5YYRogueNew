// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "PlayerStatsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API UPlayerStatsSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	int32 Gold;
	int32 XP;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetGold();
};
