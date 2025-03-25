// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
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

	UPROPERTY(EditAnywhere)
	float PatrolRadius;
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius;
	
	TScriptDelegate<UE::Core::Private::TScriptDelegateTraits<FWeakObjectPtr>::ThreadSafetyMode> OnMoveCompletedDelegate;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

	UFUNCTION()
	void OnMoveCompleted();
};
