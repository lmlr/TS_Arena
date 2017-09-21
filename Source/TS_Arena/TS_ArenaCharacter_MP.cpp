// Fill out your copyright notice in the Description page of Project Settings.

#include "TS_ArenaCharacter_MP.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "Base_Pickup.h"

// This should include all gameplay specifics for the Player Character
// e.g. Health, Stamina, Weapon...


ATS_ArenaCharacter_MP::ATS_ArenaCharacter_MP()
{
	// Default constructor

	// Create a Sphere to collect Pickups like Health and Ammo
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetupAttachment(RootComponent);
	// TODO gets overwritten by BP, find better way
	PickupSphereRadius = 100.f;
	PickupSphere->SetSphereRadius(100.f);

	// Create a Box for world interaction
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	// TODO gets overwritten by BP, find better way
	InteractionBox->InitBoxExtent({ 64.f, 48.f, 100.f });

	// Set Initial values
	if (Role == ROLE_Authority)
	{
		MaxHealth = 100.f;
		CurrentHealth = MaxHealth;
	}

}

void ATS_ArenaCharacter_MP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Add ALL replicated variables or crash and burn terribly
	DOREPLIFETIME(ATS_ArenaCharacter_MP, PickupSphereRadius);
	DOREPLIFETIME(ATS_ArenaCharacter_MP, MaxHealth);
	DOREPLIFETIME(ATS_ArenaCharacter_MP, CurrentHealth);
}

void ATS_ArenaCharacter_MP::ClientCollectItem()
{
	// Call Server Function here
	ServerCollectItem();
}

bool ATS_ArenaCharacter_MP::ServerCollectItem_Validate()
{
	// TODO some real validation
	return true;
}

void ATS_ArenaCharacter_MP::ServerCollectItem_Implementation()
{
	if (Role == ROLE_Authority)
	{
		// Array of overlapping actors to fill
		TArray<AActor*> OverlappingActors;
		FString Names;
		int Nums = 0;
		InteractionBox->GetOverlappingActors(OverlappingActors, ABase_Pickup::StaticClass());
		for (AActor* Actor : OverlappingActors)
		{
			Names.Append(Actor->GetClass()->GetName());
			Names.Append(" ");
			Nums++;
			Cast<ABase_Pickup>(Actor)->Collected(this);
		}
		UE_LOG(LogTemp, Warning, TEXT("Found a total of %d with Names: %s"), Nums, *Names)


	}
}

bool ATS_ArenaCharacter_MP::ServerDeltaHealthEvent_Validate(float DeltaHealth)
{

	// TODO some real validation
	return true;
}

void ATS_ArenaCharacter_MP::ServerDeltaHealthEvent_Implementation(float DeltaHealth)
{
	if (Role == ROLE_Authority)
	{
		CurrentHealth += DeltaHealth;
	}
}

