// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugActorUtility.h"


// Sets default values
ADebugActorUtility::ADebugActorUtility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADebugActorUtility::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADebugActorUtility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADebugActorUtility::TestFunc1()
{
	/*
	if (CollidedActor->Implements<UIProjectile>())
	{
		FString NameObj = UKismetSystemLibrary::GetDisplayName(CollidedActor); 
		UE_LOG(LogTemp, Warning, TEXT("Yes this uses interface: %s"), *NameObj);
	}*/
}

