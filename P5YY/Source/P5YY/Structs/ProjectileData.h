#pragma once

#include "ProjectileData.generated.h"

USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ProjetileId;

	
	FProjectileData()
	{
	}
};
