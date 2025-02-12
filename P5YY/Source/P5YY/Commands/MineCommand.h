// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "MineCommand.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class P5YY_API UMineCommand : public UCommand
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta=(ExposeOnSpawn))
	AActor* NewActor;
public:
	virtual void TestCall() override;
};
