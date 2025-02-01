// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACDebuffHandling.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class P5YY_API UACDebuffHandling : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UACDebuffHandling();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* Add an item to the players inventory.
	* @param Applies Debuff to this unit
	*/
	UFUNCTION(BlueprintCallable, Category="Debuff")
	void ApplyDebuff();
};
