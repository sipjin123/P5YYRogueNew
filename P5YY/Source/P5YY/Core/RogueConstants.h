#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RogueConstants.generated.h"

UCLASS()
class P5YY_API URogueConstants : public UObject
{
	GENERATED_BODY()
public:
	/** The constant string stored in the header file */
	inline static const FString MyConstantString = TEXT("Hello from header file!");
	
	/** Returns the constant string for Blueprint access */
	UFUNCTION(BlueprintPure, Category = "Constants")
	static FString GetMyConstantString() { return MyConstantString; }
	
	/** Returns the constant string for Blueprint access */
	UFUNCTION(BlueprintPure, Category = "Constants")
	static FString GetMyShorterConstantString() { return TEXT("Hello from header file!"); }
};
