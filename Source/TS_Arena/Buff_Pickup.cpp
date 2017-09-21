// Fill out your copyright notice in the Description page of Project Settings.

#include "Buff_Pickup.h"
#include "TS_ArenaCharacter_MP.h"

ABuff_Pickup::ABuff_Pickup()
{
	DeltaHealth = 20.f;
}

void ABuff_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	// Check if Health is not at max
	if (!FMath::IsNearlyZero(Collector->GetMaxHealth() - Collector->GetCurrentHealth()))
	{
		// If not at max, consume and heal
		if (Role == ROLE_Authority)
		{
			Super::Collected_Implementation(Collector);

			UE_LOG(LogTemp, Warning, TEXT("Super worked super"))

			Collector->ServerDeltaHealthEvent(DeltaHealth);
		}

	}
	
}
