// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon_Pickup.h"

ABaseWeapon_Pickup::ABaseWeapon_Pickup()
{

}

void ABaseWeapon_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	Super::Collected_Implementation(Collector);
}
