// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleSpawner.h"
#include "BountyDashGameMode.h"
#include "Obstacle.h"
#include "BountyDashTargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Floor.h"
#include "Components/SphereComponent.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(Scene);
	RootComponent = Scene;
	SpawnTimer = 1.5f;
}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	/** fill the SpawnTargets   */
	TArray<AActor*> FoundTargetPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABountyDashTargetPoint::StaticClass(), FoundTargetPointActors);
	
	for (auto Actor : FoundTargetPointActors)
	{
		ABountyDashTargetPoint* TestActor = Cast<ABountyDashTargetPoint>(Actor);
		if (TestActor)
		{
			SpawnTargets.AddUnique(TestActor);
		}
	}
	
	/** find the floor and retrieve corresponding data */
	TArray<AActor*> FoundFloorActors;
	TArray<AFloor*> Floors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFloor::StaticClass(), FoundFloorActors);

	for (auto Actor : FoundFloorActors)
	{
		AFloor* TestActor = Cast<AFloor>(Actor);
		if (TestActor)
		{
			Floors.AddUnique(TestActor);
		}
	}

	/** we need only one valid floor actor in the world */
	if (Floors.Num() > 1 && !Floors.IsValidIndex(0))
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR! One floor actor requires for this level! Remove all redundant floors ..."));
		return;
	}
	else
	{
		if (Floors[0]->GetWorld() == GetWorld())
		{
			KillPoint = Floors[0]->GetKillPoint();
			SpawnPoint = Floors[0]->GetSpawnPoint();
		}
		TimeSinceLastSpawn = SpawnTimer;
	}
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastSpawn += DeltaTime;

	float GameLevelInFloat = 1.f;

	ABountyDashGameMode* BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode());
	if (BountyDashGameMode)
	{
		GameLevelInFloat = BountyDashGameMode->GetGameLevel();
	}

	float TrueSpawnTime = SpawnTimer / GameLevelInFloat;
	if (TimeSinceLastSpawn > TrueSpawnTime)
	{
		TimeSinceLastSpawn = 0.0f;
		SpawnObstacle();
	}
}

void AObstacleSpawner::SpawnObstacle()
{
	if (SpawnTargets.Num() > 0 && ObstaclesToSpawn.Num() > 0)
	{
		short Spawner = FMath::Rand() % SpawnTargets.Num();
		short Obstical = FMath::Rand() % ObstaclesToSpawn.Num();
		float CapsuleOffset = 0.0f;

		FActorSpawnParameters SpawnInfo;
		FTransform myTrans = SpawnTargets[Spawner]->GetTransform();
		myTrans.SetLocation(FVector(SpawnPoint, myTrans.GetLocation().Y, myTrans.GetLocation().Z + 25.f));
		
		AObstacle* newObs = GetWorld()->SpawnActor<AObstacle>(ObstaclesToSpawn[Obstical], myTrans, SpawnInfo);
		if (newObs)
		{
			newObs->SetKillPoint(KillPoint);

			USphereComponent* obsSphere = Cast<USphereComponent>(newObs->GetComponentByClass(USphereComponent::StaticClass()));
			if (obsSphere)
			{
				newObs->AddActorLocalOffset(FVector(0.0f, 0.0f, obsSphere->GetUnscaledSphereRadius()));
			}

		}
	}
}

