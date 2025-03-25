// Fill out your copyright notice in the Description page of Project Settings.


#include "STTGetRandomPatrolLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "P5YY/AI/AAICharacter.h"

EStateTreeRunStatus USTTGetRandomPatrolLocation::EnterState(FStateTreeExecutionContext& Context,
                                                            const FStateTreeTransitionResult& Transition)
{
	OnMoveCompletedDelegate.BindUFunction(this, "OnMoveCompleted");
	
	AActor* actor = GetOwnerActor(Context);
	AAAICharacter* pawn = Cast<AAAICharacter>(actor);

	FNavLocation NavLocation;
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	NavSystem->GetRandomReachablePointInRadius(pawn->SpawnPosition, PatrolRadius, NavLocation);

	AAIController* aiController = Cast<AAIController>(pawn->Controller);
	EPathFollowingRequestResult::Type requestResult = aiController->MoveToLocation(NavLocation.Location, AcceptanceRadius, false);

	aiController->ReceiveMoveCompleted.AddUnique(OnMoveCompletedDelegate);
	return EStateTreeRunStatus::Running;
}

void USTTGetRandomPatrolLocation::OnMoveCompleted()
{
	FinishTask();
}



