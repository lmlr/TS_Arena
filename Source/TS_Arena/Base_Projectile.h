// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Projectile.generated.h"

UCLASS()
class TS_ARENA_API ABase_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Projectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// needed for the delegate function to register correctly
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile",
		meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile",
		meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile",
		meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ProjectileMesh;

	// Owner already stored in the AActor* Owner base class (SpawnParamter)
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile",
	//	meta = (AllowPrivateAccess = "true"))
	//class APlayerController* OwningPlayerController;
	
};
