// Fill out your copyright notice in the Description page of Project Settings.

#include "Barracks.h"
#include "Particles/ParticleSystemComponent.h"
#include "BarracksUnit.h"

// Sets default values
ABarracks::ABarracks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	SetRootComponent(BuildingMesh);

	SpawnPoint = CreateDefaultSubobject<UParticleSystemComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABarracks::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ABarracks::SpawnUnit, SpawnInterval, true);
}

// Called every frame
void ABarracks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarracks::SpawnUnit()
{
	if (UnitToSpawn)
	{
		FVector SpawnLocation = SpawnPoint->GetComponentLocation();
		GetWorld()->SpawnActor(UnitToSpawn, &SpawnLocation);
	}
}

void ABarracks::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

