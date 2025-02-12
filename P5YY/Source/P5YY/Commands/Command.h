// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class P5YY_API UCommand : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) // Just callable in blueprints
	virtual void Execute(AActor* Receiver) PURE_VIRTUAL(UCommand::Execute, );
	
	UFUNCTION(BlueprintCallable) // Just callable in blueprints
	virtual void TestCall() PURE_VIRTUAL(UCommand::TestCall, ;);

	UFUNCTION(BlueprintCallable) // Can be Handled in CPP File
	virtual void JustVirtualTest();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) // Exposed on Event Tab in Blueprint
	void NonVirtualTest();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) // Exposed on Function Tab in Blueprint
	void EKillUnit() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) // Allows creating base functionalities in C++ and overridden in BP
	void ETestEvent();
};
