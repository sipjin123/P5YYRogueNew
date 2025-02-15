// Fill out your copyright notice in the Description page of Project Settings.
// Learn more from :https://github.com/ChusMM/CppDesingPatterns/blob/master/Source/CppDesignPatterns/AchievementManager.cpp

#include "StatObserverManager.h"

#include "StatNotification.h"

bool UStatObserverManager::Instantiated_ = false;

UStatObserverManager::UStatObserverManager()
{
	// Check if the class is being created as a CDO (i.e., at the editor startup).
	// If that's the case, we allow its creation without affecting the only-one-instance behaviour.
	if (!HasAnyFlags(RF_ClassDefaultObject)) {
		//verifyf(!Instantiated_, TEXT("Trying to instance more than one class of UStatObserverManager"));
		Instantiated_ = true;
	}

	StatEventCounter.Add(EStatEvent::EVENT_ON_ASSIGNED, 0);
	StatEventCounter.Add(EStatEvent::EVENT_ON_UPDATED, 0);
	StatEventCounter.Add(EStatEvent::EVENT_DEPLETED, 0);
}

UStatObserverManager::~UStatObserverManager()
{
	Instantiated_ = false;
}

void UStatObserverManager::OnNotify(UObject* Entity, EStatEvent Event)
{
	UE_LOG(LogTemp, Warning, TEXT("NOTIFY GENERIC"));
	switch (Event) {
	case EStatEvent::EVENT_ON_ASSIGNED:
		IncreaseEventCounter(Event);
		UE_LOG(LogTemp, Warning, TEXT("Assigned"));
		if (StatEventCounter[Event] == 5) {
			Unlock(EStatEvent::EVENT_ON_ASSIGNED);
		}
		break;
	case EStatEvent::EVENT_ON_UPDATED:
		IncreaseEventCounter(Event);
		UE_LOG(LogTemp, Warning, TEXT("Updated"));
		if (StatEventCounter[Event] == 5) {
			Unlock(EStatEvent::EVENT_ON_UPDATED);
		}
		break;
	case EStatEvent::EVENT_DEPLETED:
		IncreaseEventCounter(Event);
		UE_LOG(LogTemp, Warning, TEXT("Depleted"));

		if (StatEventCounter[Event] == 5) {
			Unlock(EStatEvent::EVENT_DEPLETED);
		}
		break;
	}
}

void UStatObserverManager::IncreaseEventCounter(EStatEvent Event)
{
	// We need to keep a counter of the number of events that have arriven,
	// in order to unlock the appropriate achievements.
	// But we do not need to increase EVERY event; just the ones related to
	// the achievements.
	StatEventCounter.Add(Event, ++StatEventCounter[Event]);
}

void UStatObserverManager::Unlock(EStatEvent StatNotifType)
{
	// Save the achievement by its type, just in case we want to do something
	// with it in the future
	StatNotification CurrentStatNotif = StatNotification(StatNotifType);
	StatNotifications.Add(StatNotifType, CurrentStatNotif);

	// Run the achievement custom behaviour
	CurrentStatNotif.RunBehaviour();
}