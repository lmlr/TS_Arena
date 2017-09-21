// Fill out your copyright notice in the Description page of Project Settings.

#include "Buff_Pickup.h"

void ABuff_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP * Collector)
{
	Super::Collected_Implementation(Collector);

	UE_LOG(LogTemp, Warning, TEXT("Super worked super"))
}
