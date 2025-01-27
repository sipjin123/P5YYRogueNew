#pragma once

#include "ProjectileData.generated.h"

USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ProjectileId = -1;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileRange = 500.0f;
	
	// Behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PierceCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BounceCount = 0;

	// List down targets that have been hit
	TArray<AActor*> CollidedTargets;
	
	FProjectileData()
	{
	}
};
