#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RogueEventManager.generated.h"


// Declare a delegate with two parameters
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPrintDevText, FString, Message, EDebugMsgType, MessageType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPrintWorldText, FString, Message, EDebugColor, ColorType, FVector, Location);

UCLASS(Blueprintable)
class URogueEventManager : public UObject
{
public:
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPrintDevText OnPrintDevText;
	UPROPERTY(BlueprintAssignable)
	FOnPrintWorldText OnPrintWorldText;

	UFUNCTION(BlueprintCallable)
	static void SingletonChecker();
	UFUNCTION(BlueprintCallable)
	static URogueEventManager* Get(); // Singleton accessor
	
private:
	// Internal instance
	static URogueEventManager* Instance;
};