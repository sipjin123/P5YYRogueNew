#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
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
};