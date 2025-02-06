// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolingSubsystem.h"
#include "P5YY/Combat/AProjectile.h"

void UPoolingSubsystem::InitializePool()
{
	if (PooledObjectClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				AAProjectile* PoolableActor = World->SpawnActor<AAProjectile>(PooledObjectClass, FVector().ZeroVector, FRotator().ZeroRotator);
				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UPoolingSubsystem::OnPooledObjectDespawned);
					ObjectPool.Add(PoolableActor);
				}
			}
		}
	}
}

void UPoolingSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	InitEventCalledInBlueprint();
}

AAProjectile* UPoolingSubsystem::SpawnPooledObject()
{
	for (AAProjectile* PoolableProjectile : ObjectPool)
	{
		if (PoolableProjectile != nullptr && !PoolableProjectile->IsPoolActive())
		{
			//PoolableProjectile->TeleportTo(FVector(0,0,0), FRotator(0,0,0));
			PoolableProjectile->SetPoolLifeSpan(PooledObjectLifeSpan);
			PoolableProjectile->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableProjectile->GetPoolIndex());
			return  PoolableProjectile;
		}
	}

	// Reset oldest into latest
	if (SpawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		AAProjectile* PoolableActor = ObjectPool[PooledObjectIndex];
		if (PoolableActor != nullptr)
		{
			SpawnedPoolIndexes.Remove(PooledObjectIndex);

			PoolableActor->SetActive(false);
			PoolableActor->TeleportTo(FVector(0,0,0), FRotator(0,0,0));
			PoolableActor->SetPoolLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());

			return PoolableActor;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No Pool found from: %d"), ObjectPool.Num());
	return nullptr;
}

void UPoolingSubsystem::OnPooledObjectDespawned(AAProjectile* PooledActor)
{
	SpawnedPoolIndexes.Remove(PooledActor->GetPoolIndex());
}
