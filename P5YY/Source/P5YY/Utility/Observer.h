#pragma once

#include "CoreMinimal.h"
#include "P5YY/Enums/StatEvent.h"
#include "Observer.generated.h"

// UE4 interface.
// More info at: https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Interfaces/

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UObserver : public UInterface
{
	GENERATED_BODY()
};

// Add interface functions to this class. 
// This is the class that will be inherited to implement this interface.
class P5YY_API IObserver
{
	GENERATED_BODY()

public:
	virtual void OnNotify(UObject* Entity, EStatEvent Event) = 0;
};





// OBSOLETE
/*
#pragma once

#include "CoreMinimal.h"
#include "Observer.generated.h"

DECLARE_MULTICAST_DELEGATE(FSomethingChanged);

UCLASS()
class P5YY_API UObserver : public UObject
{
	GENERATED_BODY()
public:
	UObserver();
	
	FSomethingChanged OnSomethingChanged;

	void ChangeSomething()
	{
		OnSomethingChanged.Broadcast();
	}
};*/