// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon_Pickup.h"
#include "TS_ArenaCharacter_MP.h"

ABaseWeapon_Pickup::ABaseWeapon_Pickup()
{

}

void ABaseWeapon_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	if (Role == ROLE_Authority)
	{
		//Super::Collected_Implementation(Collector);
		ClientBroadcastPickup();

		UE_LOG(LogTemp, Warning, TEXT("Weapon Pickup Collected"))
		this->AttachToComponent(Cast<USceneComponent>(Collector->GetMesh()),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GunSocket");
	}
}

void ABaseWeapon_Pickup::ClientBroadcastPickup_Implementation()
{
	this->SetActorEnableCollision(false);
	UE_LOG(LogTemp, Warning, TEXT("PickupBroadcast was called on a Client"))
}



