// Fill out your copyright notice in the Description page of Project Settings.


#include "Command.h"

void UCommand::JustVirtualTest()
{
}

void UCommand::ETestEvent_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Test Event is Called on Base Command"));
}
