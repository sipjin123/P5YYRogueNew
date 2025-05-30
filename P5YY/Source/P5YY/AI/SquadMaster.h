﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquadMaster.generated.h"

UCLASS()
class P5YY_API ASquadMaster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASquadMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TestFunc();
	
};
