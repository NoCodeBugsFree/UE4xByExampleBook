// Fill out your copyright notice in the Description page of Project Settings.

#include "NSPlayerState.h"
#include "Net/UnrealNetwork.h"

void ANSPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANSPlayerState, Health);
	DOREPLIFETIME(ANSPlayerState, Deaths);
	DOREPLIFETIME(ANSPlayerState, Team);

	// Score is replicated in APlayerState class
	// DOREPLIFETIME(ANSPlayerState, Score);

}
