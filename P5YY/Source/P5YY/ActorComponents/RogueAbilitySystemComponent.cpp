// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "P5YY/Characters/ProtagonistChar.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"


void URogueAbilitySystemComponent::RegisterComboTagOld(int32 ComboSection)
{
	const int32 Step = ComboSection;
	const FString ComboWindowText = "Combo.Window";
	const FString ComboWindowResult = ComboWindowText + FString::FromInt(Step);

	if (GetOwner()->HasAuthority())
	UE_LOG(LogTemp, Error, TEXT("== %s"), *ComboWindowResult);
	
	// During Notify or montage end
	AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(*ComboWindowResult));


	FTimerHandle& CooldownHandle = AbilityCooldownTimers.FindOrAdd(ComboSection);
	FTimerDelegate CooldownFinishedDelegate;
	CooldownFinishedDelegate.BindUFunction(this, FName("CloseComboWindow"), ComboSection);
	
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, CooldownFinishedDelegate, 3, false);
}

void URogueAbilitySystemComponent::CloseComboWindowOld(int32 CooldownId)
{
	const FString ComboWindowText = "Combo.Window";
	const FString ComboWindowResult = ComboWindowText + FString::FromInt(CooldownId);

	if (GetOwner()->HasAuthority())
	UE_LOG(LogTemp, Log, TEXT("Cooldown finished for ability: %d -- %s"), CooldownId, *ComboWindowResult);

	RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(*ComboWindowResult));
	AbilityCooldownTimers.Remove(CooldownId);
}

// Fill out your copyright notice in the Description page of Project Settings.

void URogueAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		/*
		if (const UPXIIGameplayAbility* PXIIAbility = Cast<UPXIIGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(PXIIAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}*/
	}
}

void URogueAbilitySystemComponent::AddCharacterAbility(TSubclassOf<UGameplayAbility> EquipAbility,
	FGameplayTag inputTag)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(EquipAbility, 1);
	/*
	if (const UPXIIGameplayAbility* PXIIAbility = Cast<UPXIIGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.DynamicAbilityTags.AddTag(inputTag);
		GiveAbility(AbilitySpec);
	}*/
}

void URogueAbilitySystemComponent::RemoveCharacterAbility(const TSubclassOf<UGameplayAbility> abilityToRemove)
{
	for(FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if(Spec.Ability && Spec.Ability->GetClass() == abilityToRemove)
		{
			ClearAbility(Spec.Handle);
			break;
		}
	}
}

void URogueAbilitySystemComponent::RemoveCharacterAbilities(	const TArray<TSubclassOf<UGameplayAbility>> abilitiesToRemove)
{
	for (TSubclassOf<UGameplayAbility> abilityToRemove : abilitiesToRemove)
	{
		RemoveCharacterAbility(abilityToRemove);
	}
}


void URogueAbilitySystemComponent::TryActivateAbilityUsingEvent(const FGameplayTag& InputTag)
{
	ACharacter* MyCharacter = Cast<ACharacter>(GetAvatarActor());
	FGameplayEventData EventData;

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	
	// TODO: Optimize checks
	if (InputTag.ToString().Equals(TEXT("InputTag.LCtrl")))
	{
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Player.Movement.Dodge"));
		const FVector2D LastInputVector2D = Cast<AProtagonistChar>(MyCharacter)->GetCameraRelativeInput();
		
		// Option A: Use EventMagnitude to pass float-like vector component (simpler for magnitude)
		EventData.EventMagnitude = LastInputVector2D.Size();
		Data->HitResult.ImpactPoint = FVector(
		FMath::RoundToInt(LastInputVector2D.X),
		FMath::RoundToInt(LastInputVector2D.Y),
		0.f//FMath::RoundToInt(LastInputVector.Z)
		);
	}
	if (InputTag.ToString().Equals(TEXT("InputTag.LMB")))
	{
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Combo"));
		
		//GetOwner()->HasAuthority() && 
		/*
		if (HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.ParryCounter"))))
		{
			EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Ability.ParryCounter"));
		}*/
		const FVector LastInputVector = MyCharacter->GetMovementComponent()->GetLastInputVector(); // Use Location field to store vector
		
		// Option A: Use EventMagnitude to pass float-like vector component (simpler for magnitude)
		EventData.EventMagnitude = MyCharacter->GetMovementComponent()->GetLastInputVector().Size();
		Data->HitResult.ImpactPoint = FVector(
		FMath::RoundToInt(LastInputVector.X),
		FMath::RoundToInt(LastInputVector.Y),
		FMath::RoundToInt(LastInputVector.Z)
		);
	}

	/* TODO(Burlin):This got randomly broken, fix later
	if (InputTag.MatchesTag(FPXIIIGameplayTags::Get().InputTag_Q))
	{
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Player.Movement.Dodge"));
	}
	else if (InputTag.MatchesTag(FPXIIIGameplayTags::Get().InputTag_LMB))
	{
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Combo"));
	}*/

	bool CommitAbility = true;
	//InputTag.MatchesTag(FPXIIIGameplayTags::Get().InputTag_Q)
	//|| (InputTag.MatchesTag(FPXIIIGameplayTags::Get().InputTag_LMB) && !HasMatchingGameplayTag((FGameplayTag::RequestGameplayTag("Cooldown.Shoot"))));

	if (CommitAbility)
	{
		EventData.Instigator = MyCharacter;
		EventData.Target = MyCharacter;
		EventData.TargetData = Data;
	
		HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

void URogueAbilitySystemComponent::TryActivateAbilityUsingEventDirection(const FVector OriginLoc, const FVector Direction, const FGameplayTag& TagUsed)
{
	ACharacter* MyCharacter = Cast<ACharacter>(GetAvatarActor());
	FGameplayEventData EventData;
	
	EventData.EventTag = TagUsed;
	//EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Parry"));
	
	EventData.Instigator = MyCharacter;
	EventData.Target = MyCharacter;

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
		
	Data->HitResult.Location = FVector(
	FMath::RoundToInt(OriginLoc.X),
	FMath::RoundToInt(OriginLoc.Y),
	FMath::RoundToInt(OriginLoc.Z)
	);

	Data->HitResult.ImpactPoint = FVector(
	FMath::RoundToInt(Direction.X),
	FMath::RoundToInt(Direction.Y),
	FMath::RoundToInt(Direction.Z)
	);

	EventData.TargetData = Data;
	HandleGameplayEvent(EventData.EventTag, &EventData);
}

void URogueAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.IsActive())
			{
				UE_LOG(LogTemp, Log, TEXT("Ability Spec Activated: %s"), *InputTag.ToString())
				//InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void URogueAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				// TODO(BURLIN): Make this dynamic later to allow other abilities to use them
				// Allow client directional input for dodges
				const bool IsDodgeKey = InputTag.ToString().Equals(TEXT("InputTag.LCtrl"));
				const bool IsMeleeKey = InputTag.ToString().Equals(TEXT("InputTag.LMB"));

				if (IsDodgeKey || (IsMeleeKey && HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Player.Weapon.Action.Melee")) && !HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Player.Weapon.Action.ADS"))))
				{
					TryActivateAbilityUsingEvent(InputTag);
				}
				else
				{
					TryActivateAbility(AbilitySpec.Handle);
				}
			}
		}
	}
}

void URogueAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
			//InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}

void URogueAbilitySystemComponent::RegisterComboTag(int32 ComboSection)
{
	const int32 Step = ComboSection;
	const FString ComboWindowText = "Player.Weapon.Combo.Window";
	const FString ComboWindowResult = ComboWindowText + FString::FromInt(Step);

	if (GetOwner()->HasAuthority() && ShowComboLogs)
	{
		UE_LOG(LogTemp, Error, TEXT("Registering Combo: %s"), *ComboWindowResult);
	}
	
	// During Notify or montage end
	AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(*ComboWindowResult));


	FTimerHandle& CooldownHandle = AbilityCooldownTimers.FindOrAdd(ComboSection);
	FTimerDelegate CooldownFinishedDelegate;
	CooldownFinishedDelegate.BindUFunction(this, FName("CloseComboWindow"), ComboSection);

	const float ComboWindowTime = 1.5f;
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, CooldownFinishedDelegate, ComboWindowTime, false);
}

void URogueAbilitySystemComponent::CloseComboWindow(int32 CooldownId)
{
	const FString ComboWindowText = "Player.Weapon.Combo.Window";
	const FString ComboWindowResult = ComboWindowText + FString::FromInt(CooldownId);

	if (GetOwner()->HasAuthority() && ShowComboLogs)
	{
		UE_LOG(LogTemp, Log, TEXT("Combo Window has Closed: %s"), *ComboWindowResult);
	}
	
	FTimerHandle& CooldownHandle = AbilityCooldownTimers.FindOrAdd(CooldownId);
	GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
	CooldownHandle.Invalidate();
	
	RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(*ComboWindowResult));
	AbilityCooldownTimers.Remove(CooldownId);
}

void URogueAbilitySystemComponent::ServerRegisterInputDirectionFromClient_Implementation(FVector InputDirection)
{
	LastClientInputDirection = InputDirection;
}

void URogueAbilitySystemComponent::ServerRegisterLastInputDirectionFromClient_Implementation(FVector InputDirection)
{
	LastClientInputDirection = InputDirection;
}

void URogueAbilitySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(URogueAbilitySystemComponent, LastClientInputDirection, COND_None, REPNOTIFY_OnChanged);
}

void URogueAbilitySystemComponent::RemoveTagsInCategory(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag ParentTag)
{
	if (!AbilitySystemComponent) return;

	FGameplayTagContainer OwnedTags;
	AbilitySystemComponent->GetOwnedGameplayTags(OwnedTags);

	TArray<FGameplayTag> TagsToRemove;
	for (const FGameplayTag& Tag : OwnedTags)
	{
		if (Tag.MatchesTag(ParentTag))  // Check if the tag is within the subcategory
		{
		UE_LOG(LogTemp,Warning,TEXT("MARK Tag:{%s}"), *Tag.ToString());
			TagsToRemove.Add(Tag);
		}
	}

	for (const FGameplayTag& Tag : TagsToRemove)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
		
		// Notify all clients to sync tag removal
		Multicast_NotifyTagsRemoved(AbilitySystemComponent, TagsToRemove);
	}
}

void URogueAbilitySystemComponent::Multicast_NotifyTagsRemoved_Implementation(
	UAbilitySystemComponent* AbilitySystemComponent, const TArray<FGameplayTag>& TagsToRemove)
{
	if (!AbilitySystemComponent) return;

	for (const FGameplayTag& Tag : TagsToRemove)
	{
		UE_LOG(LogTemp,Warning,TEXT("Removed Tag:{%s}"), *Tag.ToString());
		AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
	}
}

void URogueAbilitySystemComponent::RemoveSpecificTag(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag Tag)
{
	Multicast_NotifyTagRemoved(AbilitySystemComponent, Tag);
}

void URogueAbilitySystemComponent::NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle,
                                                         UGameplayAbility* Ability)
{
	Super::NotifyAbilityActivated(Handle, Ability);
	float duration = 0;
	if(Ability->GetCooldownGameplayEffect() && Ability->GetCooldownGameplayEffect()->DurationPolicy == EGameplayEffectDurationType::HasDuration)
	{
		Ability->GetCooldownGameplayEffect()->DurationMagnitude.GetStaticMagnitudeIfPossible(1, duration);
	}
	
	OnGameplayAbilityActivated.Broadcast(Ability->GetClass()->GetName(), duration);
}

void URogueAbilitySystemComponent::Multicast_NotifyTagRemoved_Implementation(
	UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag TagToRemove)
{
	if (!AbilitySystemComponent) return;
	AbilitySystemComponent->RemoveLooseGameplayTag(TagToRemove);
}
