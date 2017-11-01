// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch8GameModeBase.h"
#include "DebugActor.h"

void ACh8GameModeBase::SpawnDebugActorAtLocation(FVector Location)
{
	if (DebugActorType)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			
			FVector SpawnLocation = Location;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			
			ADebugActor* Spawned = World->SpawnActor<ADebugActor>(DebugActorType, SpawnLocation, SpawnRotation, SpawnParams);
			if (Spawned)
			{
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WhatToSpawn == NULL"));
	}
}
