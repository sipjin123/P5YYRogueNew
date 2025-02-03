#pragma once
#include "P5YY/Enums/BuffType.h"
#include "BuffData.generated.h"

USTRUCT(BlueprintType)
struct FBuffData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuffType BuffType = EBuffType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStackable = false;
	
	FBuffData()
	{
		BuffType = EBuffType::None;
		Duration = 0.0f;
		IsStackable = false;
	}
};
