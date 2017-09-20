// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TS_ArenaGameMode.h"
#include "TS_ArenaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATS_ArenaGameMode::ATS_ArenaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
