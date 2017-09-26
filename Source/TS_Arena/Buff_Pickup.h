// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pickup.h"
#include "Buff_Pickup.generated.h"

/**
 * 
 */

UENUM()
enum class EBuffType : uint8
{
	Health 		UMETA(DisplayName = "Health"),
	Ammo		UMETA(DisplayName = "Ammo"),
	Damage		UMETA(DisplayName = "Damage"),
	Armor		UMETA(DisplayName = "Armor")
};

UCLASS()
class TS_ARENA_API ABuff_Pickup : public ABase_Pickup
{
	GENERATED_BODY()

	ABuff_Pickup();

	virtual void Collected_Implementation(class ATS_ArenaCharacter_MP* Collector) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Stats")
	float DeltaHealth;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float DeltaAmmo;

	UPROPERTY(EditAnywhere, Category = "Stats")
	EBuffType BuffType;
	
};
