#include "RogueEventManager.h"

// Need to declare this otherwise the linker cant find where the instance actually exist
URogueEventManager* URogueEventManager::Instance = nullptr;
URogueEventManager* URogueEventManager::Get()
{
	//static URogueEventManager* Instance = NewObject<URogueEventManager>();
	//return Instance;

	if (!Instance)
	{
		Instance = NewObject<URogueEventManager>();
		Instance->AddToRoot(); // Prevents garbage collection
	}
	return Instance;
}

void URogueEventManager::SingletonChecker()
{
	UE_LOG(LogTemp, Warning, TEXT("Singleton Function Called!"));
}
