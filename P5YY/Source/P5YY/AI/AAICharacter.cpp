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
		UE_LOG(LogTemp, Warning, TEXT("AI Base Attribute Success"));
		BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
		
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetManaAttribute()).AddUObject(this, &AAAICharacter::OnManaUpdated);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).AddUObject(this, &AAAICharacter::OnHealthUpdated);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Base Attribute Fail"));
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

void AAAICharacter::OnHealthUpdated(const FOnAttributeChangeData& Data) const
{
	// Fire the callback. Data contains more than NewValue, in case it is needed.
	OnHealthChange.Broadcast(Data.NewValue);
}

void AAAICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAAICharacter, BaseAttributeSet);
	DOREPLIFETIME(AAAICharacter, IsDead);
	DOREPLIFETIME(AAAICharacter, IsAttacking);
}
