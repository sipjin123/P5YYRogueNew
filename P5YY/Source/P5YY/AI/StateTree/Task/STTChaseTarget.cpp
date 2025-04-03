// Fill out your copyright notice in the Description page of Project Settings.


#include "STTChaseTarget.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

float USTTChaseTarget::GetDistanceFromTarget()
{
	if(!IsValid(TargetActor))
	{
		return 0;
	}

	DistanceToTarget = FVector::Distance(TargetActor->GetActorLocation(), OwnerActor->GetActorLocation());

	return DistanceToTarget;
}

void USTTChaseTarget::GetDistanceFromOrigin()
{
	if(!IsValid(TargetActor))
	{
		return;
	}

	if(ReturningToPatrol)
	{
		return;
	}

	float distance = FVector::Distance(CastedActor->SpawnPosition, TargetActor->GetActorLocation());
	if(distance > MaxChaseDistance)
	{
		ReturnToPatrol();
	}
}

void USTTChaseTarget::ReturnToPatrol()
{
	ReturningToPatrol = true;
	OwnerController->StopMovement();
	OwnerController->MoveToLocation(CastedActor->SpawnPosition, 5.0, false);
	OwnerController->ReceiveMoveCompleted.AddDynamic(this, &USTTChaseTarget::OnReturnToPatrolCompleted);
}

void USTTChaseTarget::OnReturnToPatrolCompleted(FAIRequestID RequestId, EPathFollowingResult::Type RequestStatus)
{
	StateTree->SendStateTreeEvent(ReturnToPatrolTag);
	UE_LOG(LogTemp, Log, TEXT("CHASE COMPLETED"));
	FinishTask(false);
}

void USTTChaseTarget::OnChaseCompleted(FAIRequestID RequestId, EPathFollowingResult::Type RequestStatus)
{
	GetDistanceFromTarget();
	UE_LOG(LogTemp, Log, TEXT("CHASE COMPLETED : DIstance from Target: %f AttackRadius : %f"), DistanceToTarget, AttackRadius);

	if(RequestStatus == EPathFollowingResult::Success)
	{
		FinishTask();
	}
	else
	{
		FinishTask(false);
	}
}

EStateTreeRunStatus USTTChaseTarget::EnterState(FStateTreeExecutionContext& Context,
                                                const FStateTreeTransitionResult& Transition)
{
	UE_LOG(LogTemp, Log, TEXT("ENTERED CHASE"));
	
	ReturningToPatrol = false;
	CastedActor = Cast<AAAICharacter>(OwnerActor);
	OwnerController = Cast<AAIController>(CastedActor->Controller);

	if(!IsValid(CastedActor))
	{
		UE_LOG(LogTemp, Log, TEXT("CHASE failed"));
		return EStateTreeRunStatus::Failed;
	}

	GetDistanceFromTarget();
	if(DistanceToTarget < AttackRadius)
	{
		return EStateTreeRunStatus::Succeeded;
	}
	
	GetDistanceFromOrigin();

	if(!ReturningToPatrol)
	{
		OwnerController->MoveToActor(TargetActor, AttackRadius * 0.5, false);
		OwnerController->ReceiveMoveCompleted.AddDynamic(this, &USTTChaseTarget::OnChaseCompleted);
	}
	
	return EStateTreeRunStatus::Running;
}
