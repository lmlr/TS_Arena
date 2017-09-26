// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup_Spawner.h"
#include "Classes/Components/BoxComponent.h"
#include "Base_Pickup.h"
#include "Engine/World.h"

// Sets default values
APickup_Spawner::APickup_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningVolume"));

	PickupClass = nullptr;

	CurrentlyActivePickup = nullptr;
}

// Called when the game starts or when spawned
void APickup_Spawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnPickup();
}

// Called every frame
void APickup_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup_Spawner::SpawnPickup()
{
	if (Role == ROLE_Authority && PickupClass)
	{
		auto Origin = SpawningVolume->Bounds.Origin;
		auto Extent = SpawningVolume->Bounds.BoxExtent;
		auto SpawnPoint = Origin;
		FActorSpawnParameters SpawnParams;
		FRotator SpawnRotation = { 0,0,0 };
		ABase_Pickup* Pickup = GetWorld()->
			SpawnActor<ABase_Pickup>(PickupClass, SpawnPoint, SpawnRotation, SpawnParams);
		
		// Set the currently active Pickup
		CurrentlyActivePickup = Pickup;

		// Associate this spawner with the created Pickup
		CurrentlyActivePickup->SetSpawnVolume(this);
	}
}

void APickup_Spawner::PickupWasCollected()
{
	if (Role == ROLE_Authority && CurrentlyActivePickup)
	{
		// Tell the Pickup that it no longer belongs to this spawner
		CurrentlyActivePickup->SetSpawnVolume(nullptr);
		
		// Set the Currently held (active) Pickup to null
		CurrentlyActivePickup = nullptr;
		
		// Set a timer for respawn
		UE_LOG(LogTemp, Warning, TEXT("Pickup collection called on spawner"))
	}
}

