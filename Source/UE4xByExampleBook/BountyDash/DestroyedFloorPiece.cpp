// Fill out your copyright notice in the Description page of Project Settings.

#include "DestroyedFloorPiece.h"
#include "Components/SceneComponent.h"

// Sets default values
ADestroyedFloorPiece::ADestroyedFloorPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(RootComponent);

	/*Destructable = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructable"));
	check(Destructable);

	Destructable->SetupAttachment(RootComponent);
	Destructable->SetCollisionProfileName("OverlapAllDynamic");*/

	InitialLifeSpan = 4.f;
}

// Called when the game starts or when spawned
void ADestroyedFloorPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyedFloorPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
