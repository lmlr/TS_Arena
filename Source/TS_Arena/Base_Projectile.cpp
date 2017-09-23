// Fill out your copyright notice in the Description page of Project Settings.

#include "Base_Projectile.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Classes/Components/StaticMeshComponent.h"


// Sets default values
ABase_Projectile::ABase_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bReplicateMovement = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	RootComponent = CollisionSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->SetUpdatedComponent(CollisionSphere);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CollisionSphere);
}

// Called when the game starts or when spawned
void ABase_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

