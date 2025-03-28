// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Components/StateTreeComponent.h"
#include "P5YY/AI/AAICharacter.h"
#include "P5YY/AI/AvatarAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "STTIsPlayerSighted.generated.h"

/**
 * 
 */

UCLASS()
class P5YY_API USTTIsPlayerSighted : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Output")
	FVector SpawnPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Output")
	TObjectPtr<AActor> TargetActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float MaxChaseDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Context")
	TObjectPtr<AActor> OwnerActor;

protected:
	UAIPerceptionComponent* AiPerceptionComponent;
	AAAICharacter* AiCharacter;
	AAvatarAIController* AiController;
	UStateTreeComponent* StateTree;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);
	
	UFUNCTION()
	void HandleSightPerception(AActor* Actor, FAIStimulus Stimulus);
};
