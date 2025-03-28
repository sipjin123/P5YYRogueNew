// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "P5YY/AI/AAICharacter.h"
#include "STTAiStrafe.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API USTTAiStrafe : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Context")
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEnvQuery> TargetQuery;

protected:
	FVector TargetDestination;
	AAIController* AiController;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

	UFUNCTION()
	void OnStrafeQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
};
