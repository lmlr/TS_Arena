// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pickup.h"
#include "Buff_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class TS_ARENA_API ABuff_Pickup : public ABase_Pickup
{
	GENERATED_BODY()
	
	virtual void Collected_Implementation(class ATS_ArenaCharacter_MP* Collector) override;
	
	
};
