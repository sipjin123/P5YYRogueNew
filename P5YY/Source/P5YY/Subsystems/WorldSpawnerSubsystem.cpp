// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSpawnerSubsystem.h"

#include "P5YY/AI/AAICharacter.h"
#include "P5YY/Framework/EnemyFactory.h"

void UWorldSpawnerSubsystem::SpawnEnemy(TSubclassOf<AAAICharacter> CustomAI, FVector Location, FRotator Rotation)
{
	UWorld* World = GetWorld();
	if (World)
	{
		// Use this if Create Enemy Function is Static
		// AAAICharacter* Goblin = UEnemyFactory::CreateEnemy(World, CustomAI->StaticClass(), Location, Rotation);
		
		UEnemyFactory* Spawner = NewObject<UEnemyFactory>();
		AAAICharacter* Goblin = Spawner->CreateEnemy(CustomAI, Location, Rotation, World);
		
		UE_LOG(LogTemp, Warning, TEXT("Enemy Should Spawn now from World"));
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("World is MISSING!"));
	}
}

void UWorldSpawnerSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	InitEventCalledInBlueprint();
}
