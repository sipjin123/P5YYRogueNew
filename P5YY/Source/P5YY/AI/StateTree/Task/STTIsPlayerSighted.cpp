// Fill out your copyright notice in the Description page of Project Settings.


#include "STTIsPlayerSighted.h"
#include "Components/StateTreeComponent.h"
#include "P5YY/AI/AAICharacter.h"
#include "P5YY/AI/AvatarAIController.h"
#include "P5YY/Characters/ProtagonistChar.h"
#include "Perception/AISense_Sight.h"


EStateTreeRunStatus USTTIsPlayerSighted::EnterState(FStateTreeExecutionContext& Context,
                                                    const FStateTreeTransitionResult& Transition)
{
	AiCharacter = Cast<AAAICharacter>(OwnerActor);
	if(IsValid(AiCharacter) && !OwnerActor->HasAuthority())
	{
		return EStateTreeRunStatus::Failed;
	}

	AiController = Cast<AAvatarAIController>(AiCharacter->Controller);
	if(!IsValid(AiController))
	{
		UE_LOG(LogTemp, Log, TEXT("Controller Not Valid"));
		return EStateTreeRunStatus::Failed;
	}

	StateTree = OwnerActor->GetComponentByClass<UStateTreeComponent>();
	if(!IsValid(StateTree))
	{
		UE_LOG(LogTemp, Log, TEXT("StateTree is not found"))
		return EStateTreeRunStatus::Failed;
	}
	
	AiPerceptionComponent = AiController->AIPerceptionComponent;
	if(!IsValid(AiPerceptionComponent))
	{
		UE_LOG(LogTemp, Log, TEXT("AiPerceptionComponent Not Valid"));
		return EStateTreeRunStatus::Failed;
	}
	
	AiPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &USTTIsPlayerSighted::OnPerceptionUpdated);
	AiPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &USTTIsPlayerSighted::OnTargetPerceptionForgotten);

	UE_LOG(LogTemp, Log, TEXT("AI Perception is setup"));

	return EStateTreeRunStatus::Running;
}

void USTTIsPlayerSighted::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Log, TEXT("OnPerceptionUpdated ActorName: %s IsSuccessful: %s"), *Actor->GetName(), Stimulus.WasSuccessfullySensed() ? TEXT("TRUE") : TEXT("FALSE"));

	HandleSightPerception(Actor, Stimulus);
}

void USTTIsPlayerSighted::OnTargetPerceptionForgotten(AActor* Actor)
{
	UE_LOG(LogTemp, Log, TEXT("OnTargetPerceptionForgotten %s"), *Actor->GetName());

	TargetActor = nullptr;
}


void USTTIsPlayerSighted::HandleSightPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if(UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus)->GetName() != UAISense_Sight::StaticClass()->GetName())
	{
		// Handles only the sight perception
		return;
	}

	if(!Stimulus.WasSuccessfullySensed() && IsValid(TargetActor))
	{
		if(TargetActor == Actor)
		{
			if(FVector::Distance(OwnerActor->GetActorLocation(), TargetActor->GetActorLocation()) < MaxChaseDistance)
			{
				return;				
			}
			UE_LOG(LogTemp, Log, TEXT("Removing Target"))
			TargetActor = nullptr;
			return;
		}
	}
	
	if(IsValid(TargetActor))
	{
		return;
	}
	
	if (AiCharacter->IsDead)
	{
		// If AI is dead don't do anything
		return;
	}

	if (!Actor->ActorHasTag(TEXT("Player")))
	{
		// If sensed actor is not Player don't do anything.
		// Remove this to include any AI ally of player in detection
		return;
	}

	AProtagonistChar* targetChar = Cast<AProtagonistChar>(Actor);
	if (!IsValid(targetChar))
	{
		return;
	}

	bool onTheSameTeam = targetChar->FactionType == AiCharacter->FactionType;
	if (AiCharacter->FactionType == EFactionType::Neutral || onTheSameTeam)
	{
		// If Ai and target actor is on the same team don't do anything
		return;
	}
	float distance = FVector::Distance(SpawnPosition, targetChar->GetActorLocation());
	if (distance > MaxChaseDistance)
	{
		return;
	}

	TargetActor = Actor;
	AiCharacter->TargetActor =  Actor;
	
	FStateTreeEvent StateTreeEvent;
	StateTreeEvent.Tag = FGameplayTag::RequestGameplayTag(TEXT("State.Chase"));
	StateTree->SendStateTreeEvent(StateTreeEvent);	
}

