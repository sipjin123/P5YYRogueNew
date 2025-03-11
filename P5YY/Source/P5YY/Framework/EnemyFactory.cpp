// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "P5YY/AI/AAICharacter.h"

AAAICharacter* UEnemyFactory::CreateEnemy(TSubclassOf<AAAICharacter> EnemyClass, FVector Location, FRotator Rotator, UObject * WorldContextObject)
{
	UWorld * World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	if (World && *EnemyClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy will now Create"));
		return World->SpawnActor<AAAICharacter>(EnemyClass, Location, Rotator);
	}
	if (!World)
		UE_LOG(LogTemp, Warning, TEXT("Enemy Failed to Create World"));
	if (!*EnemyClass)
		UE_LOG(LogTemp, Warning, TEXT("Enemy Failed to Create Actor"));
	return nullptr;
}
