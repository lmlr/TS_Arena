// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pickup.h"
#include "BaseWeapon_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class TS_ARENA_API ABaseWeapon_Pickup : public ABase_Pickup
{
	GENERATED_BODY()

	ABaseWeapon_Pickup();

	virtual void Collected_Implementation(class ATS_ArenaCharacter_MP* Collector) override;
	
	UFUNCTION(NetMulticast, Reliable)
	void ClientBroadcastPickup();
};
