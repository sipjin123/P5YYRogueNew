// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ASSESSORS(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class P5YY_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UBaseAttributeSet();

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//UFUNCTION()
	//virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UPROPERTY(BlueprintReadOnly, Category="AttributesNew", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ASSESSORS(UBaseAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category="AttributesNew", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ASSESSORS(UBaseAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, Category="AttributesNew", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ASSESSORS(UBaseAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category="AttributesNew", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ASSESSORS(UBaseAttributeSet, MaxMana);
	
public:
	
	UFUNCTION(BlueprintCallable)
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION(BlueprintCallable)
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	
	UFUNCTION(BlueprintCallable)
	void OnRep_MaxHealth(const FGameplayAttributeData& OldHMaxealth);
	
	UFUNCTION(BlueprintCallable)
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
};
