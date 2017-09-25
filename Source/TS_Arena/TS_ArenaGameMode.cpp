// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TS_ArenaGameMode.h"
#include "TS_ArenaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TS_ArenaCharacter_MP.h"

ATS_ArenaGameMode::ATS_ArenaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

bool ATS_ArenaGameMode::ServerSpawnCharacter_Validate(class AController* Controller)
{
	// TODO some real validation
	return true;
}

void ATS_ArenaGameMode::ServerSpawnCharacter_Implementation(class AController* Controller)
{
	// Authority guard not necessary 
	if (Controller)
	{
		// Check if this controlles a valid pawn
		if (auto Pawn = Controller->GetPawn())
		{
			// destroy the currently controlled pawn
			Controller->UnPossess();
			Pawn->Destroy();
		}
		auto NextSpawn = ChoosePlayerStart(Controller);
		FActorSpawnParameters SpawnParams;
		auto Loc = NextSpawn->GetActorTransform();
		auto NewCharacter = GetWorld()->SpawnActor<ATS_ArenaCharacter_MP>(CharacterSpawnClass, Loc, SpawnParams);
		Controller->Possess(NewCharacter);
	}
}