// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyFactory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class P5YY_API UEnemyFactory : public UObject
{
	GENERATED_BODY()
	
public:
    // Function to create an enemy // Use TSubclassOf<AAAICharacter> if there are child classes
    UFUNCTION(BlueprintCallable, Category = "Spawning", meta = (WorldContext = WorldContextObject))
    //static AAAICharacter* CreateEnemy(UWorld* World, TSubclassOf<AAAICharacter> EnemyClass, FVector Location, FRotator Rotator);
	AAAICharacter* CreateEnemy(TSubclassOf<AAAICharacter> EnemyClass, FVector Location, FRotator Rotator, UObject * WorldContextObject);
};