// Fill out your copyright notice in the Description page of Project Settings.

#include "Buff_Pickup.h"
#include "TS_ArenaCharacter_MP.h"

ABuff_Pickup::ABuff_Pickup()
{
	DeltaHealth = 20.f;
	DeltaAmmo = 10.f;
}

// IMPORTANT: ONLY activate overlaps on the collision sphere of the Pickup,
// the mesh overlap would trigger the effect again
// TODO only trigger overlapevent on the sphere, codeside implementation!
void ABuff_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	// Check if Health is not at max
	if (Role == ROLE_Authority)
	{
		// Do something based on Pickup Type
		switch (BuffType)
		{
		case EBuffType::Health:
		{
			// If not at max, consume and heal
			if (!FMath::IsNearlyZero(Collector->GetMaxHealth() - Collector->GetCurrentHealth()))
			{
				Super::Collected_Implementation(Collector);

				UE_LOG(LogTemp, Warning, 
					TEXT("HealthPickup was colleced by %s"), *Collector->GetName())

				// TODO currently passing NULL, might want to change this
				Collector->ServerDeltaHealthEvent(DeltaHealth, nullptr);
			}
		}
		case EBuffType::Ammo:
		{
			// Ammo Pickup Logic
		}
		case EBuffType::Damage:
		{
			// Damage Pickup Logic
		}
		case EBuffType::Armor:
		{
			// Armor Pickup Logic
		}
		}
		

	}
	
}
