// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueGameState.h"
#include "P5YY/Utility/StatObserverManager.h"


ARogueGameState::ARogueGameState()
{
}

UStatObserverManager* ARogueGameState::GetAStatObserverManager()
{
	// If the AchievementManager has not been instanced yet, instance it
	// 
	// Why don't we override the HandleBeginPlay()? Because we don't know
	// when that method will be executed, and we have to make sure the instance
	// exists before any other BeginPlay event
	if (!StatObserverManager.IsValid()) {
		// Notice how UObjects must be instanced with the NewObject factory
		// method instead of "new".
		StatObserverManager = NewObject<UStatObserverManager>();
	}

	return StatObserverManager.Get();
}
