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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
	class USphereComponent* GetPickupSphere() const { return PickupSphere; }

private:
	UPROPERTY(Replicated, EditAnywhere, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	float PickupSphereRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class USphereComponent* PickupSphere;

	UPROPERTY(VisibleAnywhere, Category = "Pickup",
		meta = (AllowPrivateAccess = "false"))
	class UBoxComponent* InteractionBox;
	
	
};
