// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TS_Arena_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TS_ARENA_API ATS_Arena_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATS_Arena_PlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	int GetFrags() { return Frags; };

	int GetDeaths() { return Deaths; };

	void IncrementFrags() { Frags++; };

	void IncrementDeaths() { Deaths++; };

private:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats",
		meta = (AllowPrivateAccess = "true"))
	int Frags;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats",
		meta = (AllowPrivateAccess = "true"))
	int Deaths;

};
