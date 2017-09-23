// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon_Pickup.h"
#include "TS_ArenaCharacter_MP.h"
#include "Net/UnrealNetwork.h"
#include "Classes/Components/SkeletalMeshComponent.h"

ABaseWeapon_Pickup::ABaseWeapon_Pickup()
{	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	if (Role == ROLE_Authority)
	{
		bool bInUse = false;

		MyOwner = nullptr;
	}
	
}

void ABaseWeapon_Pickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseWeapon_Pickup, bInUse)

}

void ABaseWeapon_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	if (Role == ROLE_Authority && !bInUse)
	{
		//Super::Collected_Implementation(Collector);
		ClientBroadcastPickup(Collector);

		UE_LOG(LogTemp, Warning, TEXT("Weapon Pickup Collected"))
		this->AttachToComponent(Cast<USceneComponent>(Collector->GetMesh()),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GunSocket");

		bInUse = true;
		MyOwner = Collector;
	}
}

void ABaseWeapon_Pickup::ClientBroadcastPickup_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	this->SetActorEnableCollision(false);
	Collector->SetEquipedWeapon(this);
	UE_LOG(LogTemp, Warning, TEXT("PickupBroadcast was called on a Client"))
}

bool ABaseWeapon_Pickup::ServerDropped_Validate(class ATS_ArenaCharacter_MP* Collector)
{
	return true;
}


void ABaseWeapon_Pickup::ServerDropped_Implementation(class ATS_ArenaCharacter_MP* Collector)
{
	if (Role == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Drop Was Called on Server"))
		this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		ClientBroadcastDrop(Collector);

		MyOwner = nullptr;
		bInUse = false;
	}
}

void ABaseWeapon_Pickup::ClientBroadcastDrop_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	// Should probably NOT all be done client-side
	bReplicateMovement = true;
	this->SetActorEnableCollision(true);
	FVector DropOffset = Collector->GetActorForwardVector();
	this->AddActorWorldOffset(DropOffset*200.f);
	UE_LOG(LogTemp, Warning, TEXT("DropBroadcast was called on a Client"))
	Collector->SetEquipedWeapon(nullptr);
}

