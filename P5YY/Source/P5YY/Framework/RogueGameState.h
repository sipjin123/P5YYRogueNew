// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RogueGameState.generated.h"

/**
 * 
 */
class StatObserverManager;
UCLASS(Blueprintable)
class P5YY_API ARogueGameState : public AGameStateBase
{
	GENERATED_BODY()
	ARogueGameState();
public:
	UFUNCTION(BlueprintCallable, Category = "Achievements")
	UStatObserverManager* GetAStatObserverManager();

private:
	TWeakObjectPtr<UStatObserverManager> StatObserverManager;
};