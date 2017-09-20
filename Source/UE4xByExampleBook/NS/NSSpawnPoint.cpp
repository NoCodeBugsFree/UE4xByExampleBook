// Fill out your copyright notice in the Description page of Project Settings.

#include "NSSpawnPoint.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ANSSpawnPoint::ANSSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SpawnCapsule->SetCollisionProfileName("OverlapAllDynamic");
	SpawnCapsule->bGenerateOverlapEvents = true;

	SpawnCapsule->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);

	OnActorBeginOverlap.AddDynamic(this, &ANSSpawnPoint::ActorBeginOverlaps);
	OnActorEndOverlap.AddDynamic(this, &ANSSpawnPoint::ActorEndOverlaps);

	/** 
		This actor will be loaded on network clients during map load. 
		Only our server is concerned with spawning the players. This object does not
		need to exist on the client.
	*/
	bNetLoadOnClient = false;
}

// Called when the game starts or when spawned
void ANSSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANSSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnCapsule->UpdateOverlaps();
}

void ANSSpawnPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (Team == ETeam::RED_TEAM)
	{
		SpawnCapsule->ShapeColor = FColor(255, 0, 0);
	}
	else // (Team == ETeam::BLUE_TEAM)
	{
		SpawnCapsule->ShapeColor = FColor(0, 0, 255);
	}
}

void ANSSpawnPoint::ActorBeginOverlaps(AActor* OverlapedActor, AActor* OtherActor)
{
	if (Role == ROLE_Authority)
	{
		/** if we have not OtherActor in our OverlappingActors array - add it into the array  */
		if (OverlappingActors.Find(OtherActor) == INDEX_NONE)
		{
			OverlappingActors.Add(OtherActor);
		}
	}
}

void ANSSpawnPoint::ActorEndOverlaps(AActor* OverlapedActor, AActor* OtherActor)
{
	if (Role == ROLE_Authority)
	{
		/** if we have not OtherActor in the OverlappingActors array - remove it from the array   */
		if (OverlappingActors.Find(OtherActor) != INDEX_NONE)
		{
			OverlappingActors.Remove(OtherActor);
		}
	}
}
