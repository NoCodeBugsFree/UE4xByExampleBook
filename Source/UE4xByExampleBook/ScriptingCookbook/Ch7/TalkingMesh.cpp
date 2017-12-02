// Fill out your copyright notice in the Description page of Project Settings.

#include "TalkingMesh.h"
#include "ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"

ATalkingMesh::ATalkingMesh()
{
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
		GetStaticMeshComponent()->bGenerateOverlapEvents = true;
	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	SetActorEnableCollision(true);
}

void ATalkingMesh::StartTalking_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Hello there. What is your name?"));
}

void ATalkingMesh::StartCrying_Implementation(FVector Vector, int32 Value)
{
	UE_LOG(LogTemp, Error, TEXT("Vector = %s  Value = %d"), *Vector.ToString(), Value);
}
