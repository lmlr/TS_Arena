// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TS_ArenaGameMode.generated.h"

UCLASS(minimalapi)
class ATS_ArenaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATS_ArenaGameMode();



	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpawnCharacter(class AController* Controller);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATS_ArenaCharacter> CharacterSpawnClass;
};



