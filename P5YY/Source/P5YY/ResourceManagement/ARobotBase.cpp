﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ARobotBase.h"


// Sets default values
AARobotBase::AARobotBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinerActiveData = NewObject<UMinerActiveData>();
}

// Called when the game starts or when spawned
void AARobotBase::BeginPlay()
{
	MinerActiveData = NewObject<UMinerActiveData>();
	Super::BeginPlay();
}

// Called every frame
void AARobotBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AARobotBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

