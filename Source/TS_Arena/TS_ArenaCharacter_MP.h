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

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void ClientCollectItem();

	UFUNCTION(Server, Reliable, WithValidation, Category = "Pickup")
	void ServerCollectItem();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetMaxHealth() { return MaxHealth; };

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetCurrentHealth() { return CurrentHealth; };

private:
	UPROPERTY(Replicated, EditAnywhere, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	float PickupSphereRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class USphereComponent* PickupSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* InteractionBox;

	UPROPERTY(Replicated, EditAnywhere, Category = "Stats",
		meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(Replicated, EditAnywhere, Category = "Stats",
		meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;
	
};
