// Fill out your copyright notice in the Description page of Project Settings.

#include "NSGameState.h"
#include "Net/UnrealNetwork.h"

void ANSGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANSGameState, bIsInMenu);
}
