// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PoolingSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class P5YY_API UPoolingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)

	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();

	UFUNCTION(BlueprintCallable)
	void InitializePool();
protected:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;

	UFUNCTION(BlueprintCallable)
	AAProjectile* SpawnPooledObject();

	UPROPERTY(EditAnywhere, Category="ObjectPool")
	TSubclassOf<class AAProjectile> PooledObjectClass;

	UPROPERTY(EditAnywhere, Category="ObjectPool")
	int PoolSize = 20;
	
	UPROPERTY(EditAnywhere, Category="ObjectPool")
	float PooledObjectLifeSpan = 2.0f;

	UFUNCTION()
	void OnPooledObjectDespawned(AAProjectile* PooledActor);

	TArray<AAProjectile*> ObjectPool;
	
	TArray<int> SpawnedPoolIndexes;
};
