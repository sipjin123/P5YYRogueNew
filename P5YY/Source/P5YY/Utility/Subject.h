
#pragma once

#include "Containers/Array.h"
#include "P5YY/Enums/StatEvent.h"
#include "Subject.generated.h"

class IObserver;

UCLASS(BlueprintType)
class P5YY_API USubject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Observer Pattern")
	void AddObserver(TScriptInterface<IObserver> Observer);

	UFUNCTION(BlueprintCallable, Category = "Observer Pattern")
	void RemoveObserver(TScriptInterface<IObserver> Observer);

protected:
	UFUNCTION(BlueprintCallable, Category = "Observer Pattern")
	void Notify(UObject* Entity, EStatEvent Event);

private:
	// UINTERFACES generate their destructor private,
	// so shared pointer can't access it to manage its life cycle,
	// thus giving us an error at compile time if we try to use them.
	TArray<IObserver*> Observers;
};