// Fill out your copyright notice in the Description page of Project Settings.


#include "STTAiStrafe.h"

#include "AIController.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/PathFollowingComponent.h"

EStateTreeRunStatus USTTAiStrafe::EnterState(FStateTreeExecutionContext& Context,
                                             const FStateTreeTransitionResult& Transition)
{
	UE_LOG(LogTemp, Log, TEXT("STRAFE ENTER STATE"))

	APawn* aiPawn = Cast<APawn>(OwnerActor);
	AiController = Cast<AAIController>(aiPawn->Controller);
	UEnvQueryInstanceBlueprintWrapper* EQSInstance = UEnvQueryManager::RunEQSQuery(GetWorld(),  TargetQuery, TargetActor, EEnvQueryRunMode::AllMatching, nullptr);
	EQSInstance->GetOnQueryFinishedEvent().Clear();
	EQSInstance->GetOnQueryFinishedEvent().AddDynamic(this, &USTTAiStrafe::OnStrafeQueryFinished);
	
	return EStateTreeRunStatus::Running;
}

void USTTAiStrafe::OnStrafeQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	TArray<FVector> Result;
	QueryInstance->GetQueryResultsAsLocations(Result);
	int randIndex = FMath::RandRange(0, Result.Num() - 1);
	TargetDestination = Result[randIndex];
	
	EPathFollowingRequestResult::Type result = AiController->MoveToLocation(TargetDestination, 0.5, false);
	AiController->ReceiveMoveCompleted.Clear();
	AiController->ReceiveMoveCompleted.AddDynamic(this, &USTTAiStrafe::OnMoveCompleted);
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), TargetDestination, 10, 12, FLinearColor::White, 5);
}

void USTTAiStrafe::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	UE_LOG(LogTemp, Log, TEXT("STRAFE COMPLETED"))

	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), TargetActor->GetActorLocation());
	OwnerActor->SetActorRotation(targetRotation);
	
	if(Result == EPathFollowingResult::Success)
	{
		FinishTask();
	}
	else
	{
		FinishTask(false);
	}
}
