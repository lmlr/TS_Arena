// Fill out your copyright notice in the Description page of Project Settings.

#include "Base_Pickup.h"
#include "TS_ArenaCharacter_MP.h"
#include "Net/UnrealNetwork.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Pickup_Spawner.h"

// Sets default values
ABase_Pickup::ABase_Pickup()
{
	// Important for Multiplayer... obviously :D
	bReplicates = true;
	// If movement is important: Add
	// bReplicateMovement = true;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("FuckingROOT"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	Mesh->SetupAttachment(Root);
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetupAttachment(Root);
	
	bIsActive = true;

	SpawnVolume = nullptr;

}

void ABase_Pickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABase_Pickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABase_Pickup, bIsActive)
}

bool ABase_Pickup::Collected_Validate(ATS_ArenaCharacter_MP* Collector)
{
	return true;
}


void ABase_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP* Collector)
{
	// this should manage gameplay functionality (e.g. stats)
	if (Role == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s was collected by %s"), *this->GetName(),
			*Collector->GetName())

		this->SetLifeSpan(0.1f);
		ClientCollected();
		
		// disassociate the pickup from the spawn volume
		if (SpawnVolume)
		{
			SpawnVolume->PickupWasCollected();
		}

	}
}

void ABase_Pickup::ClientCollected_Implementation()
{
	// this should manage client side fluff (particles etc)
	
	UE_LOG(LogTemp, Warning, TEXT("This Ran on a Client"))
	
}

void ABase_Pickup::SetSpawnVolume(APickup_Spawner * NewSpawnVolume)
{
	if (Role == ROLE_Authority)
	{
		SpawnVolume = NewSpawnVolume;
	}
}