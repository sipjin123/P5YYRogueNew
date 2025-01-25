// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMineable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHasDepleted);
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIMineable : public UInterface
{
	GENERATED_BODY()
};

class P5YY_API IIMineable
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Harvesting")
	bool IsMineable();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Harvesting")
	float GetMaxResource();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Harvesting")
	float GetRemainingResource();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Harvesting")
	void DeductResource(float Value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Harvesting")
	void DepleteResource();
};
