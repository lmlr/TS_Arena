// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Pickup.generated.h"

UCLASS()
class TS_ARENA_API ABase_Pickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Pickup();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(Server, Reliable, WithValidation)
	void Collected(class ATS_ArenaCharacter_MP* Collector);

	UFUNCTION(NetMulticast, Reliable)
	void ClientCollected();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Pickup")
	bool bIsActive;
	
	
};
