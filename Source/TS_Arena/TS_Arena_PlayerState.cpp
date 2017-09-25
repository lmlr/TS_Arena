// Fill out your copyright notice in the Description page of Project Settings.

#include "TS_Arena_PlayerState.h"
#include "Net/UnrealNetwork.h"

ATS_Arena_PlayerState::ATS_Arena_PlayerState()
{
	Frags = 0;
	Deaths = 0;
}

void ATS_Arena_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATS_Arena_PlayerState, Frags)
	DOREPLIFETIME(ATS_Arena_PlayerState, Deaths)
}
