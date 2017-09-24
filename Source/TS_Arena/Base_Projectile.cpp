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
	// Only do this on the server
	if (Role == ROLE_Authority)
	{	
		// check if the overlapping actor is of class TS_ArenaCharacter_MP
		if(OtherActor->IsA(ATS_ArenaCharacter_MP::StaticClass()))
		{
			// check that we are not overlapping with ourself
			if (this->GetOwner() != Cast<ATS_ArenaCharacter_MP>(OtherActor)->GetController())
			{
				ProjectileHandleCollision(OtherActor, true);
			}
		}
		
		else
		{
			// Handle overlap events with different actors (e.g. world static)
			ProjectileHandleCollision(OtherActor, false);
		}
			
	}
}

bool ABase_Projectile::ProjectileHandleCollision_Validate(AActor* HitTarget, bool bHitPlayer)
{
	// TODO some real validation
	return true;
}

void ABase_Projectile::ProjectileHandleCollision_Implementation(AActor* HitTarget, bool bHitPlayer)
{
	if (Role == ROLE_Authority)
	{
		// Did we hit a Player directly?
		if (bHitPlayer)
		{
			// Deal Damage to the Player
			Cast<ATS_ArenaCharacter_MP>(HitTarget)->ServerDeltaHealthEvent(-20.f);
			// Activate visual effects on all clients
		}
		// Logic for hitting something else
		else
		{
			// Activate visual effects on all clients

			// some other logic (radial dmg?)
		}
		Destroy();
	}
}

void ABase_Projectile::ClientProjectileCollision_Implementation()
{

}