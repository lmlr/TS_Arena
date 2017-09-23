// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pickup.h"
#include "BaseWeapon_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class TS_ARENA_API ABaseWeapon_Pickup : public ABase_Pickup
{
	GENERATED_BODY()
public:
	ABaseWeapon_Pickup();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void Collected_Implementation(class ATS_ArenaCharacter_MP* Collector) override;
	
	FTimerHandle WeaponFireTimer;

	UFUNCTION(NetMulticast, Reliable)
	void ClientBroadcastPickup(ATS_ArenaCharacter_MP * Collector);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerDropped(class ATS_ArenaCharacter_MP* Collector);

	UFUNCTION(NetMulticast, Reliable)
	void ClientBroadcastDrop(ATS_ArenaCharacter_MP * Collector);

	UFUNCTION(Server, Reliable, WithValidation)
	void StartFiring();

	UFUNCTION(NetMulticast, Reliable)
	void SpawnProjectile();

	void SetFireActive(bool bNewVal) { bFireActive = bNewVal; };

private:
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Pickup")
	bool bInUse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class ATS_ArenaCharacter_MP* MyOwner;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Pickup")
	bool bFireActive;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	int Ammo;

	// Projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABase_Projectile> ProjectileClass;
};
