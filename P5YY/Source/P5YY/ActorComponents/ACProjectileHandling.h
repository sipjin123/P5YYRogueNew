// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P5YY/Structs/ProjectileData.h"
#include "ACProjectileHandling.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class P5YY_API UACProjectileHandling : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UACProjectileHandling();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
	bool IsLogicActive = false;
	
	UPROPERTY(BlueprintReadWrite)
	FProjectileData ProjectileData;
};
