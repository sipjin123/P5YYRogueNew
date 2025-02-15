#include "Subject.h"
#include "Observer.h"

void USubject::AddObserver(TScriptInterface<IObserver> Observer)
{
		UE_LOG(LogTemp, Warning, TEXT("Observer was Added"));
	Observers.Add((IObserver*)Observer.GetInterface());
}

void USubject::RemoveObserver(TScriptInterface<IObserver> Observer)
{
		UE_LOG(LogTemp, Warning, TEXT("Observer was Removed"));
	Observers.Remove((IObserver*)Observer.GetInterface());
}

void USubject::Notify(UObject* Entity, EStatEvent Event)
{
	UE_LOG(LogTemp, Warning, TEXT("NOTIFY"));
	for (auto Observer : Observers) {
		
		UE_LOG(LogTemp, Warning, TEXT("NOTIFY Observer"));
		Observer->OnNotify(Entity, Event);
	}
}