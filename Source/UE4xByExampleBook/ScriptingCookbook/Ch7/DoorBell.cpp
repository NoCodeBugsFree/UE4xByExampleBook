// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorBell.h"
#include "Engine/CollisionProfile.h"
#include "ConstructorHelpers.h"
#include "Openable.h"

ADoorBell::ADoorBell()
{
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
		GetStaticMeshComponent()->bGenerateOverlapEvents = true;
		GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
		GetStaticMeshComponent()->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
		SetActorEnableCollision(true);
	}
}

bool ADoorBell::CanInteract_Implementation()
{
	return !bHasBeenPushed;
}

void ADoorBell::PerformInteract_Implementation()
{
	if (DoorToOpen)
	{
		if (DoorToOpen->GetClass()->ImplementsInterface(UOpenable::StaticClass()))
		{
			if (IOpenable* Openable = Cast<IOpenable>(DoorToOpen))
			{
				Openable->Execute_Open(DoorToOpen);
			}
		}
	}
}

