// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Engine/CollisionProfile.h"
#include "ConstructorHelpers.h"

ADoor::ADoor()
{
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
		GetStaticMeshComponent()->bGenerateOverlapEvents = true;
		GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
		GetStaticMeshComponent()->SetWorldScale3D(FVector(0.3f, 2.f, 3.f));
		SetActorEnableCollision(true);
	}
}

bool ADoor::CanInteract_Implementation()
{
	return IInteractable::CanInteract_Implementation();
}

void ADoor::PerformInteract_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("The door refuses to budge. Perhaps there is a hidden switch nearby ? "));
}

void ADoor::Open_Implementation()
{
	AddActorLocalOffset(FVector(0, 0, 200));
}
