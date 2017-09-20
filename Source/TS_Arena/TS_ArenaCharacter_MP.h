// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TS_ArenaCharacter.h"
#include "TS_ArenaCharacter_MP.generated.h"

/**
 * 
 */
UCLASS()
class TS_ARENA_API ATS_ArenaCharacter_MP : public ATS_ArenaCharacter
{
	GENERATED_BODY()
	
public:

	ATS_ArenaCharacter_MP();

	UPROPERTY(EditAnywhere, Category = "Pickup")
	class USphereComponent* PickupSphere;
	
private:
	
	
};
