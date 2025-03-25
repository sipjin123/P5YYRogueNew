#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "P5YY/Core/RogueEventManager.h"
#include "BCustomUtility.generated.h"


UCLASS()
class P5YY_API UBCustomUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static void Test(int a, int b);
	
	UFUNCTION(BlueprintCallable)
	static FVector GetViewportCamLoc();
	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject))
	static TArray<AActor*> GetActorsWithinRadius(FVector Origin, float Radius, UObject * WorldContextObject);
	UFUNCTION(BlueprintCallable)
	static FRotator GetViewportCamRot();
	UFUNCTION(BlueprintCallable)
	static FVector GetViewportForwardVector(FRotator NewRotator);

	UFUNCTION(BlueprintCallable)
	static void ApplyForceToTarget(const FVector FromLoc, const ACharacter* TargetCharacter, const float AttackForce);

	UFUNCTION(BlueprintCallable, Category = "Events")
    static void OnPrintDevText(EDebugMsgType MessageType, FString Message)
    {
        URogueEventManager::Get()->OnPrintDevText.Broadcast(Message, MessageType);
    }
	UFUNCTION(BlueprintCallable, Category = "Events")
	static void OnPrintWorldText(FVector Location, EDebugColor ColorType, FString Message)
	{
		URogueEventManager::Get()->OnPrintWorldText.Broadcast(Message, ColorType, Location);
	}
};