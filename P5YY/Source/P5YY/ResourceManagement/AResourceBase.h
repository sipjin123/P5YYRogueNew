// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P5YY/Structs/ResourceActiveData.h"
#include "P5YY/Interfaces/IMineable.h"
#include "AResourceBase.generated.h"

UCLASS()
class P5YY_API AAResourceBase : public AActor, public IIMineable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAResourceBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	class UStaticMeshComponent* StaticMeshSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	UResourceActiveData* ResourceData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	int RemainingResource = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	int MaxResource = 5;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FHasDepleted HasDepleted;
};
