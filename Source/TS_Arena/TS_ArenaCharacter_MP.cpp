// Fill out your copyright notice in the Description page of Project Settings.

#include "TS_ArenaCharacter_MP.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

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

}

void ATS_ArenaCharacter_MP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATS_ArenaCharacter_MP, PickupSphereRadius);
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
		InteractionBox->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors)
		{
			Names.Append(Actor->GetClass()->GetName());
			Names.Append(" ");
			Nums++;
		}
		UE_LOG(LogTemp, Warning, TEXT("Found a total of %d with Names: %s"), Nums, *Names)


	}
}