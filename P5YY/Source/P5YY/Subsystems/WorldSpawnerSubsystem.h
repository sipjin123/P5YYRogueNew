// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P5YY/AI/AAICharacter.h"
#include "P5YY/Enums/GameEnums.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldSpawnerSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class P5YY_API UWorldSpawnerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)

	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();

	UFUNCTION(BlueprintCallable, Category="Spawning")
	void SpawnEnemy(TSubclassOf<AAAICharacter> CustomAI, FVector Location, FRotator Rotation);
protected:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
};
