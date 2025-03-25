// Fill out your copyright notice in the Description page of Project Settings.


#include "AAICharacter.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AAAICharacter::AAAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void AAAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(AbilitySystemComponent))
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			UE_LOG(LogTemp, Warning, TEXT("AI Base Attribute Success"));
		}
		BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
		
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetManaAttribute()).AddUObject(this, &AAAICharacter::OnManaUpdated);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).AddUObject(this, &AAAICharacter::OnHealthUpdated);
	}
	else
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			UE_LOG(LogTemp, Warning, TEXT("AI Base Attribute Fail"));
		}
	}
}

// Called every frame
void AAAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsLockingOnTarget)
	{
		LockOnTargetTick(DeltaTime);
	}

	if (HasAuthority())
	{
		if (TickAnimation || (TickOnAttack && IsAttacking))
		{
			GetMesh()->TickAnimation(DeltaTime, false);
			GetMesh()->RefreshBoneTransforms();
			GetMesh()->UpdateComponentToWorld();
		}
	}
}

// Called to bind functionality to input
void AAAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAAICharacter::LockOnTargetTick(float DeltaTime)
{
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		GetActorLocation(), TargetLocation);
	NewRotation = FRotator(0.f, NewRotation.Yaw,0.f);
	
	SetActorRotation(FMath::RInterpTo(
		GetActorRotation(), NewRotation, DeltaTime, LockRotationSpeed));
}

void AAAICharacter::FKillUnit() const
{
}

void AAAICharacter::SetLockTarget(bool IsLocked, FVector NewTargetLocation)
{
	IsLockingOnTarget = IsLocked;
	TargetLocation = NewTargetLocation;
}

void AAAICharacter::OnManaUpdated(const FOnAttributeChangeData& Data) const
{
	// Fire the callback. Data contains more than NewValue, in case it is needed.
	OnManaChange.Broadcast(Data.NewValue);
}

FVector AAAICharacter::GetSocketLocation(FName SocketName)
{
	FVector SocketLocation;
	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		if (!GetMesh()->IsRegistered())
		{
			GetMesh()->RegisterComponent();
		}

		if (GetMesh()->GetAnimInstance())
		{
			// Pause animation evaluation but keep the instance active for AI movement
			GetMesh()->bPauseAnims = true;
			GetMesh()->GetAnimInstance()->SetRootMotionMode(ERootMotionMode::RootMotionFromMontagesOnly);
		}

		// Update bone transforms manually (This allows getting the exact coordinates of sockets on a dedicated server without relying on TickAnimation[Which is Costly])
		GetMesh()->RefreshBoneTransforms();
		GetMesh()->UpdateComponentToWorld();

		if (GetMesh()->GetAnimInstance())
		{
			// Optionally resume animation updates
			GetMesh()->bPauseAnims = false;

			// NOTE: This will crash the editor due to access violation, if root motion is needed, create a function else where to sync
			//GetMesh()->GetAnimInstance()->SetRootMotionMode(ERootMotionMode::RootMotionFromEverything);
		}

		// Get socket location (on both server and client)
		 SocketLocation = GetMesh()->GetSocketLocation(TEXT("MeleeSocket"));

		// Debug draw for confirmation (only visible on client)
		#if !UE_BUILD_SHIPPING
		DrawDebugSphere(GetWorld(), SocketLocation, 10.0f, 12, FColor::Red, false, 1.0f);
		#endif
	}
	return SocketLocation;
}

void AAAICharacter::OnHealthUpdated(const FOnAttributeChangeData& Data) const
{
	// Fire the callback. Data contains more than NewValue, in case it is needed.
	OnHealthChange.Broadcast(Data.NewValue);
}

float AAAICharacter::OnGetCurrentHealth_Implementation()
{
	if (BaseAttributeSet)
	{
		return  BaseAttributeSet->Health.GetBaseValue();
	}
	return 0.f;
}

float AAAICharacter::OnGetMaxHealth_Implementation()
{
	if (BaseAttributeSet)
	{
		return  BaseAttributeSet->MaxHealth.GetBaseValue();
	}
	return 100.f;
}

void AAAICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAAICharacter, BaseAttributeSet);
	DOREPLIFETIME(AAAICharacter, IsDead);
	DOREPLIFETIME(AAAICharacter, IsAttacking);
}
