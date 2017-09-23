// Fill out your copyright notice in the Description page of Project Settings.

#include "TS_ArenaCharacter_MP.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
//#include "Base_Pickup.h"
#include "BaseWeapon_Pickup.h"

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

	EquipedWeapon = nullptr;

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
	DOREPLIFETIME(ATS_ArenaCharacter_MP, EquipedWeapon);
}

void ATS_ArenaCharacter_MP::ClientCollectItem()
{
	// Call Server Function here
	ServerCollectItem();
}

void ATS_ArenaCharacter_MP::ClientDropItem()
{
	// Call Server Function here
	ServerDropItem();
}

bool ATS_ArenaCharacter_MP::ServerCollectItem_Validate()
{
	// TODO some real validation
	return true;
}

// TODO split pickup in passive and active functions (this is active)
void ATS_ArenaCharacter_MP::ServerCollectItem_Implementation()
{
	if (Role == ROLE_Authority)
	{
		// Array of overlapping actors to fill
		TArray<AActor*> OverlappingActors;
		FString Names;
		int Nums = 0;
		InteractionBox->GetOverlappingActors(OverlappingActors, ABaseWeapon_Pickup::StaticClass());
		if (OverlappingActors.Num() > 0)
		{
			// No Weapon equiped? Equip this!
			if (!EquipedWeapon)
			{
				Cast<ABaseWeapon_Pickup>(OverlappingActors[0])->Collected(this);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("I still have a weapon equiped"))
			}
		}
	}
}

bool ATS_ArenaCharacter_MP::ServerDropItem_Validate()
{
	// TODO some real validation
	return true;
}

void ATS_ArenaCharacter_MP::ServerDropItem_Implementation()
{
	if (Role == ROLE_Authority && EquipedWeapon)
	{
		EquipedWeapon->ServerDropped(this);
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

bool ATS_ArenaCharacter_MP::SetEquipedWeapon_Validate(ABaseWeapon_Pickup* Weapon)
{
	// TODO some real validation
	return true;
}

void ATS_ArenaCharacter_MP::SetEquipedWeapon_Implementation(ABaseWeapon_Pickup* Weapon)
{
	// Set the equiped Weapon. This gets set to NULL on weapon drop
	EquipedWeapon = Weapon;
	
}

void ATS_ArenaCharacter_MP::Fire()
{
	Super::Fire();
	if (EquipedWeapon)
	{
		ServerIssueFireCommand();
	}
}

void ATS_ArenaCharacter_MP::StopFiring()
{
	Super::StopFiring();
}

bool ATS_ArenaCharacter_MP::ServerIssueFireCommand_Validate()
{
	// TODO some real validation
	return true;
}

void ATS_ArenaCharacter_MP::ServerIssueFireCommand_Implementation()
{
	if (Role == ROLE_Authority)
	{
		// Tell the Weapon to fire
		UE_LOG(LogTemp, Warning, TEXT("Server tells the Weapon to fire"))
	}
}