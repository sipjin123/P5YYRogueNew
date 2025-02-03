#pragma once
#include "P5YY/Enums/DebuffType.h"
#include "DebuffData.generated.h"

USTRUCT(BlueprintType)
struct FDebuffData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDebuffType DebuffType = EDebuffType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStackable = false;
	
	FDebuffData()
	{
		DebuffType = EDebuffType::None;
		Duration = 0.0f;
		IsStackable = false;
	}
};
