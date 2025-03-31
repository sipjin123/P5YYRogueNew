// Fill out your copyright notice in the Description page of Project Settings.


#include "STTBasicAttack.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

float USTTBasicAttack::GetDistanceFromTarget()
{
	return FVector::Distance(OwnerActor->GetActorLocation(), TargetActor->GetActorLocation());
}

void USTTBasicAttack::MoveWithinAttackRadius()
{
	OwnerController->MoveToActor(TargetActor, AttackRadius * 0.5, false);
	OwnerController->ReceiveMoveCompleted.AddDynamic(this, &USTTBasicAttack::OnMoveToAttackRadiusCompleted);
}

void USTTBasicAttack::ExecuteAttack()
{
	AttackExecuted = false;
	OwnerController->StopMovement();

	bool AttackSucceeds;
	CharacterIDamageable->Execute_AttackStart(OwnerActor, AttackSlotsNeeded, TargetActor, AttackSucceeds);

	if(AttackSucceeds)
	{
		CastedCharacter->AttackEnded.Clear();
		CastedCharacter->AttackEnded.AddDynamic(this, &USTTBasicAttack::OnAttackEnded);
		CastedCharacter->Execute_AttackTarget(OwnerActor, TargetActor);
		AttackExecuted = true;
	}
	else
	{
		CharacterIDamageable->Execute_AttackEnd(OwnerActor, TargetActor);
		FinishTask(false);
	}
}

void USTTBasicAttack::OnMoveToAttackRadiusCompleted(FAIRequestID RequestID, EPathFollowingResult::Type RequestResult)
{
	if(RequestResult == EPathFollowingResult::Success)
	{
		ExecuteAttack();
	}
	else
	{
		FinishTask(false);
	}
}

void USTTBasicAttack::OnAttackEnded()
{
	FinishTask();
}

EStateTreeRunStatus USTTBasicAttack::EnterState(FStateTreeExecutionContext& Context,
                                                const FStateTreeTransitionResult& Transition)
{
	if(!IsValid(TargetActor))
	{
		return EStateTreeRunStatus::Failed;
	}

	CastedCharacter = Cast<AAAICharacter>(OwnerActor);
	OwnerController = Cast<AAIController>(CastedCharacter->Controller);
	CharacterIDamageable = Cast<IIDamageable>(OwnerActor);
	
	float dist = GetDistanceFromTarget();
	if(dist < AttackRadius)
	{
		ExecuteAttack();
	}
	else
	{
		if(dist > StrafeRadius)
		{
			return EStateTreeRunStatus::Failed;
		}
	
		MoveWithinAttackRadius();
	}
	
	return	EStateTreeRunStatus::Running;
}
