// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Components/StateTreeComponent.h"
#include "P5YY/AI/AAICharacter.h"
#include "STTChaseTarget.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API USTTChaseTarget : public UStateTreeTaskBlueprintBase
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
	float MaxChaseDistance;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Output")
	float DistanceToTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Output")
	bool ReturningToPatrol;

	UPROPERTY(EditAnywhere)
	FGameplayTag ReturnToPatrolTag;

protected:
	AAAICharacter* CastedActor;
	AAIController* OwnerController;
	UStateTreeComponent* StateTree;
	
	float GetDistanceFromTarget();
	void GetDistanceFromOrigin();

	void ReturnToPatrol();

	UFUNCTION()
	void OnReturnToPatrolCompleted(FAIRequestID RequestId, EPathFollowingResult::Type RequestStatus);
	UFUNCTION()
	void OnChaseCompleted(FAIRequestID RequestId, EPathFollowingResult::Type RequestStatus);

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
};
