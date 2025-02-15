#include "StatNotification.h"



StatNotification::StatNotification(EStatEvent StatNotifType)
{
	this->StatNotifType = StatNotifType;

	switch (StatNotifType) {
	case EStatEvent::EVENT_ON_ASSIGNED:
		this->Description = TEXT("[Achievement Assigned]!");
		break;
	case EStatEvent::EVENT_ON_UPDATED:
		this->Description = TEXT("[Achievement Updated]!");
		break;
	case EStatEvent::EVENT_DEPLETED:
		this->Description = TEXT("[Achievement Depleted]!");
		break;
	}
}

EStatEvent StatNotification::GetType() const
{
	return StatNotifType;
}

const FName& StatNotification::GetDescription() const
{
	return Description;
}

void StatNotification::RunBehaviour()
{
	// Do something with the achievement.
	// For example, print it to the viewport, reward the player with something, etc.
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, GetDescription().ToString());
}