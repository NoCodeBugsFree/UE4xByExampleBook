// Fill out your copyright notice in the Description page of Project Settings.

#include "Peasant.h"
#include "ConstructorHelpers.h"
#include "King.h"
#include "EngineUtils.h"

APeasant::APeasant()
{
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->bGenerateOverlapEvents = true;
	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

void APeasant::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AKing> Iter(GetWorld()); Iter; ++Iter)
	{
		if ((*Iter))
		{
			// first king enough
			if(AKing* King = Cast<AKing>(*Iter))
			{
				King->OnKingDeath.AddDynamic(this, &APeasant::Flee);
				return;
			}
		}	
	}
}

void APeasant::Flee(AKing* DeadKing)
{
	if (DeadKing)
	{
		FVector FleeVector = GetActorLocation() - DeadKing->GetActorLocation();
		FleeVector.Normalize();
		FleeVector *= 500;
		SetActorLocation(GetActorLocation() + FleeVector);
	}
}
