// Fill out your copyright notice in the Description page of Project Settings.


#include "ACProjectileHandling.h"


// Sets default values for this component's properties
UACProjectileHandling::UACProjectileHandling()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACProjectileHandling::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UACProjectileHandling::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

