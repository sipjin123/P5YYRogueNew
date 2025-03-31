// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "P5YY/AI/AAICharacter.h"
#include "STTBasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API USTTBasicAttack : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Context")
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<AActor> TargetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float AttackRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float StrafeRadius;

protected:
	int AttackSlotsNeeded;
	bool AttackExecuted;

	AAAICharacter* CastedCharacter;
	AAIController* OwnerController;
	IIDamageable* CharacterIDamageable;
	
	float GetDistanceFromTarget();

	void MoveWithinAttackRadius();
	void ExecuteAttack();

	UFUNCTION()
	void OnMoveToAttackRadiusCompleted(FAIRequestID RequestID, EPathFollowingResult::Type RequestResult);

	UFUNCTION()
	void OnAttackEnded();
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
};
