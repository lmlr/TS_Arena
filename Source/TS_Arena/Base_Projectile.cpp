// Fill out your copyright notice in the Description page of Project Settings.

#include "Base_Projectile.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "TS_ArenaCharacter_MP.h"



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

	// Delegate function must be bound on begin play, wont work on contructor!
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABase_Projectile::OnOverlapBegin);
}

// Called every frame
void ABase_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABase_Projectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, 
	AActor * OtherActor, UPrimitiveComponent * OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Role == ROLE_Authority)
	{	
		if(auto Controller = Cast<ATS_ArenaCharacter_MP>(OtherActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlapping Actor: %s of Class: %s"), 
				*OtherActor->GetName(), *Controller->GetController()->GetName())
		}
			
	}
}

