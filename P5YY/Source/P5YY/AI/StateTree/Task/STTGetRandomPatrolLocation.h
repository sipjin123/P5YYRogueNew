// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Navigation/PathFollowingComponent.h"
#include "UObject/ScriptDelegates.h"
#include "STTGetRandomPatrolLocation.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API USTTGetRandomPatrolLocation : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float PatrolRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float AcceptanceRadius;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
};
