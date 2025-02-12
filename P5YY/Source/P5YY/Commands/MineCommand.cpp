// Fill out your copyright notice in the Description page of Project Settings.


#include "MineCommand.h"
#include "P5YY/Subsystems/PlayerStatsSubsystem.h"

#define GET_STAT_SUBSYSTEM Getworld()->GetFirstPlayerController()->GetlocalPlayer()->GetSubsystem<UPlayerStatsSubsystem>();

/*
void UMineCommand::Execute(AActor* Receiver)
{
	//int32 NewGold = GET_STAT_SUBSYSTEM->GetGold();
	Super::Execute(Receiver);
}*/

void UMineCommand::TestCall()
{
	Super::TestCall();
}
