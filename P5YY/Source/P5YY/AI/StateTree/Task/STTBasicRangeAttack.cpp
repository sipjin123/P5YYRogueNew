// Fill out your copyright notice in the Description page of Project Settings.


#include "STTBasicRangeAttack.h"

float USTTBasicRangeAttack::GetDistanceFromTarget()
{
	return FVector::Distance(OwnerActor->GetActorLocation(), TargetActor->GetActorLocation());
}

void USTTBasicRangeAttack::ExecuteAttack()
{
	AttackExecuted = false;
	OwnerController->StopMovement();

	bool AttackSucceeds;
	CharacterIDamageable->Execute_AttackStart(OwnerActor, AttackSlotsNeeded, TargetActor, AttackSucceeds);

	if(AttackSucceeds)
	{
		CastedCharacter->AttackEnded.Clear();
		CastedCharacter->AttackEnded.AddDynamic(this, &USTTBasicRangeAttack::OnAttackEnded);
		CastedCharacter->Execute_AttackTarget(OwnerActor, TargetActor);
		AttackExecuted = true;
	}
	else
	{
		CharacterIDamageable->Execute_AttackEnd(OwnerActor, TargetActor);
		FinishTask(false);
	}
}


EStateTreeRunStatus USTTBasicRangeAttack::EnterState(FStateTreeExecutionContext& Context,
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
		return EStateTreeRunStatus::Failed;
	}
	
	return EStateTreeRunStatus::Running;
}

void USTTBasicRangeAttack::OnAttackEnded()
{
	FinishTask();
}
