// Fill out your copyright notice in the Description page of Project Settings.

#include "TS_ArenaCharacter_MP.h"
#include "Classes/Components/SphereComponent.h"

// This should include all gameplay specifics for the Player Character
// e.g. Health, Stamina, Weapon...


ATS_ArenaCharacter_MP::ATS_ArenaCharacter_MP()
{
	// Default constructor

	// Create a Sphere to collect Pickups like Health and Ammo
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	

}