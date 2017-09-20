// Fill out your copyright notice in the Description page of Project Settings.

#include "Base_Pickup.h"
#include "TS_ArenaCharacter_MP.h"

// Sets default values
ABase_Pickup::ABase_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));

}

// Called when the game starts or when spawned
void ABase_Pickup::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABase_Pickup::Collected_Validate(ATS_ArenaCharacter_MP* Collector)
{
	return true;
}


void ABase_Pickup::Collected_Implementation(ATS_ArenaCharacter_MP* Collector)
{
	if (Role == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s was collected by %s"), *this->GetName(),
			*Collector->GetName())

		this->Destroy();
	}
}