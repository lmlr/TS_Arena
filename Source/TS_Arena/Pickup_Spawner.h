// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup_Spawner.generated.h"

UCLASS()
class TS_ARENA_API APickup_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnPickup();

	void PickupWasCollected();

private:
	// Box bounds for spawning the Pickup
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawningVolume;

	// Pickup class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABase_Pickup> PickupClass;

	// Pointer to Pickup that is currently on this Spawn
	UPROPERTY(VisibleAnywhere)
	class ABase_Pickup* CurrentlyActivePickup;
	
};
