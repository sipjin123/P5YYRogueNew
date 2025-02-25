 // Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "P5YY/Interfaces/IDamageable.h"

 // Sets default values
AAProjectile::AAProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    //RootComponent = SceneComponent;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    CollisionSphere->SetSphereRadius(15);
    CollisionSphere->SetCollisionProfileName("SphereCollision");

	RootComponent = CollisionSphere;
    //CollisionSphere->SetupAttachment(RootComponent);

    StaticMeshSource = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatMeshComp"));
    StaticMeshSource->SetVisibility(true);
    StaticMeshSource->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    if (!ProjectileMovementComponent)
    {
        // Use this component to drive this projectile's movement.
    	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
    	ProjectileMovementComponent->InitialSpeed = 1500.0f;
    	ProjectileMovementComponent->MaxSpeed = 1500.0f;
    	ProjectileMovementComponent->bRotationFollowsVelocity = true;
    	ProjectileMovementComponent->bShouldBounce = true;
    	ProjectileMovementComponent->Bounciness = 0.3f;
    	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }
}

// Called when the game starts or when spawned
void AAProjectile::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = GetActorLocation();
}

// Called every frame
void AAProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

 void AAProjectile::SetStartLocation(FVector NewLocation)
 {
	SpawnLocation = NewLocation;
 }

 void AAProjectile::SetTargetLocation(FVector NewLocation)
 {
	TargetLocation = NewLocation;
 }

 void AAProjectile::SetFaction(EFactionType NewFaction)
 {
	OwnerFaction = NewFaction;
 }

 bool AAProjectile::IsPoolActive()
 {
	return Active;
 }

 void AAProjectile::SetActive(bool IsActive)
 {
	Active = IsActive;
	//SetActorHiddenInGame(!IsActive);
	if (IsActive)
	{
		GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &AAProjectile::DeactivatePoolObject, PoolLifeSpan, false);
	}
 }

void AAProjectile::DeactivatePoolObject()
{
	Active = false;
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}

 void AAProjectile::SetPoolIndex(int Index)
 {
	PoolIndex = Index;
 }

 void AAProjectile::SetPoolLifeSpan(float NewLifeSpan)
 {
	PoolLifeSpan = NewLifeSpan;
 }

 int AAProjectile::GetPoolIndex()
 {
	return  PoolIndex;
 }

 ECollisionType AAProjectile::FilterCollision(AActor* CollidedActor)
 {
	if (CollidedActor != nullptr)
	{
		bool hasCollidedWithOwner = CollidedActor == GetOwner();
		bool hasHitProjectile = CollidedActor->Implements<UIProjectile>();
		bool hasHitDamageableTarget = CollidedActor->Implements<UIDamageable>();

		// Can Skip
		if (hasCollidedWithOwner || hasHitProjectile)
		{
			return ECollisionType::Ignore;
		}
		if (hasHitDamageableTarget)
		{
			return HasAuthority() ? ECollisionType::Process : ECollisionType::Destroy;
		}
	}
	
	return ECollisionType::Ignore;
 }

 void AAProjectile::InitializeProjectileVelocity(float NewSpeed, FVector NewVelocity, FVector SpawnPoint, FRotator StartRotator)
{
	SetActorLocation(SpawnPoint);
	SetActorRotation(StartRotator);
	//ProjectileMovementComponent->Velocity = NewVelocity;
	ProjectileMovementComponent->Velocity = NewVelocity * NewSpeed;
}

 void AAProjectile::InitializeProjectile(FVector NewDirection, FVector SpawnPoint, FRotator StartRotator)
{
    SetActorLocation(SpawnPoint);
    SetActorRotation(StartRotator);
    ProjectileMovementComponent->Velocity = NewDirection * ProjectileMovementComponent->InitialSpeed;
}

 void AAProjectile::InitializeProjectile_Multicast_Implementation(FVector NewDirection, FVector SpawnPoint,
	 FRotator StartRotator)
 {
	InitializeProjectile(NewDirection, SpawnPoint, StartRotator);
 }

 void AAProjectile::InitializeProjectileTowards(FVector NewTargetLocation, FVector NewDirection, FVector SpawnPoint, FRotator StartRotator)
{
	SetActorLocation(SpawnPoint);

	FVector Forward = SpawnPoint - GetActorLocation();
	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, FVector::UpVector);
	SetActorRotation(Rot);
	//FVector Direction = UKismetMathLibrary::GetForwardVector(GetActorRotation());
    ProjectileMovementComponent->Velocity = NewDirection * ProjectileMovementComponent->InitialSpeed;
}
