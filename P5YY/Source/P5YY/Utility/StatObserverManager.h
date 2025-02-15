// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Observer.h"
#include "StatNotification.h"
#include "StatObserverManager.generated.h"

/**
 * 
 */
UCLASS()
class P5YY_API UStatObserverManager : public UObject, public IObserver
{
	GENERATED_BODY()

public:
	UStatObserverManager();
	~UStatObserverManager();

	void OnNotify(UObject* Entity, EStatEvent Event) override;

private:
	void IncreaseEventCounter(EStatEvent Event);
	void Unlock(EStatEvent StatNotifType);

private:
	TMap<EStatEvent, uint32> StatEventCounter;
	TMap<EStatEvent, StatNotification> StatNotifications;

	static bool Instantiated_;
};