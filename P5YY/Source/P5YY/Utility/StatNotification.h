#pragma once
#include "P5YY/Enums/StatEvent.h"

class StatNotification
{
public:
	StatNotification(EStatEvent StatNotifType);

	EStatEvent GetType() const;
	const FName& GetDescription() const;

	// This method could be overriden in child classes
	// to implement the custom behaviour of the concrete
	// achievement
	virtual void RunBehaviour();

private:
	FName Description;
	EStatEvent StatNotifType;
};