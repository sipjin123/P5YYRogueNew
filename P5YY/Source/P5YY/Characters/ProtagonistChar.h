// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "BaseAttributeSet.h"
#include "UtilityLibrary.h"
#include "P5YY/Combat/AProjectile.h"
#include "P5YY/ActorComponents/ACEquipmentHandling.h"
#include "P5YY/Data/CombatUnitData.h"
#include "P5YY/Enums/GameEnums.h"
#include "P5YY/Enums/PlayerActionState.h"
#include "P5YY/UIWidgets/DialogueWidgetBase.h"
#include "P5YY/UIWidgets/PlayerStatWidget.h"

#include "ProtagonistChar.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CharacterLog, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChange, int, AttributeValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInvulnerableChange, bool, InvulnerableValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStunChange, bool, StunValue);

// Forward Declaration
class URogueAbilitySystemComponent;
class URogueGameplayAbility;

UCLASS()
class P5YY_API AProtagonistChar : public ACharacter, public  IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProtagonistChar();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* StatMeshSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable")
		TSubclassOf<AAProjectile> CustomProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UACEquipmentHandling* EquipmentHandling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		FCombatUnitData CombatUnitData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UACMobilityHandling* MobilityHandling;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UACRobotUpgradeHandling* RobotUpgradeHandling;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UACInventoryHandling* InventoryHandling;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UPlayerStatWidget> PlayerHUDClass;

	UPROPERTY()
		UPlayerStatWidget* PlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ProjectileSpawnPt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InteractionDistancce = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ProjectileOffset = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		EFactionType FactionType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DialogueClass;
	class UDialogueWidgetBase* DialogueBase;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool UseBlueprintControls = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool CanLookUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool UseCPPAbilities = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool CanControlCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool IsAttacking;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
		bool IsTopDown = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentAbilitySelected;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		AActor* InteractedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		AActor* PreviousInteractedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* TargetMobilityNode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* CameraTopViewActor;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		FVector TargetMobilityLocation;
	
	UFUNCTION(BlueprintCallable, Category = "Group1")
		void LockTarget();

	UFUNCTION(BlueprintCallable, Category = "Group1")
		void AssignLockTarget(AActor* NewTargetActor);

	UFUNCTION(BlueprintCallable, Category = "Group1")
		void InitializeCustomComponents();

	UFUNCTION(BlueprintCallable, Category = "Group1")
		void UpdateEquipmentHandling();

	UFUNCTION(BlueprintCallable)
		void ToggleDialogueScene(bool IsEnabled);
protected:

	// Overrides
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category="NetworkCombat")
	void Server_SpawnProjectile(FVector newSpawnPt);
	bool Server_SpawnProjectile_Validate(FVector newSpawnPt);
	void Server_SpawnProjectile_Implementation(FVector newSpawnPt);
	
	UFUNCTION(BlueprintCallable, Category = "Group1")
	void SpawnProjectileAt(FVector newSpawnPt);

	/**
	 * Ability System Dependencies
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS", meta = (AllowPrivateAccess="true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return  AbilitySystemComponent;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS", meta = (AllowPrivateAccess="true"))
	const class UBaseAttributeSet* BaseAttributeSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS", meta = (AllowPrivateAccess="true"))
	TObjectPtr<UBaseAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category="GAS")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="GAS")
	TArray<TSubclassOf<URogueGameplayAbility>> RogueGameplayAbilities;

	UPROPERTY()
	uint8 bAbilitiesInitialized = 1;//1 bit

	// Advanced GAS and Attrib
	//------------------------------
	UFUNCTION(BlueprintImplementableEvent)
	void OnAbilityDamage (float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACharacter* InstigatorCharacter, AActor* DamageCauser);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged (float DeltaVal, const struct FGameplayTagContainer& EventTags);

	virtual void HandleDamage (float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACharacter* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChange (float DeltaVal, const struct FGameplayTagContainer& EventTags);

	friend UBaseAttributeSet;
	//------------------------------
public:
	// Allows calling teleport event across c++ and BP
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NetworkCombat")
	void NetTeleport (FVector newLoc);
	virtual void NetTeleport_Implementation(FVector newLoc);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void StartupGameplayAbilities();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PlayerActionTick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TraceInteraction();
	
	// UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing=OnRep_Mana)
	// GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URPGAttributeSet, Mana)

	// This callback can be used by the UI.
	UPROPERTY(BlueprintAssignable, Category = "Attribute callbacks")
	FAttributeChange OnManaChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EPlayerActionState PlayerActionState;
	
	// The callback to be registered within AbilitySystem.
	void OnManaUpdated(const FOnAttributeChangeData& Data) const;
	
	// This callback can be used by the UI.
	UPROPERTY(BlueprintAssignable, Category = "Attribute callbacks")
	FAttributeChange OnHealthChange;

	UPROPERTY(BlueprintAssignable, Category = "Stat callbacks")
	FInvulnerableChange OnInvulnerableChange;
	
	UPROPERTY(BlueprintAssignable, Category = "Stat callbacks")
	FStunChange OnStunChange;
	
	// The callback to be registered within AbilitySystem.
	void OnHealthUpdated(const FOnAttributeChangeData& Data) const;
};
