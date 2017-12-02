// Fill out your copyright notice in the Description page of Project Settings.

#include "King.h"
#include "ConstructorHelpers.h"

AKing::AKing()
{
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->bGenerateOverlapEvents = true;
	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

void AKing::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerDelegate DestroyDelegate;
	DestroyDelegate.BindLambda( [&] { Die();  });
	
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, DestroyDelegate, 1.f, false);
}

void AKing::Die()
{
	OnKingDeath.Broadcast(this);
}