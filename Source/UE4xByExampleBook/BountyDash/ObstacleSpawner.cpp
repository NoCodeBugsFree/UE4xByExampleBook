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
	FillTheSpawnTargetsArray();
	
	/** find the floor and retrieve corresponding data */
	FindFloorAndRetrieveData();

	/** sets the Game Mode Reference  */
	BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/** WTF is FTimerHandle ??? =)  */
	TimeSinceLastSpawn += DeltaTime;

	float GameLevelInFloat = 1.f;
	
	if (BountyDashGameMode)
	{
		GameLevelInFloat = BountyDashGameMode->GetGameLevel();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AObstacleSpawner::Tick() --- BountyDashGameMode == NULL"));
		return;
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
	if (BountyDashTargetPoints.Num() > 0 && ObstaclesToSpawn.Num() > 0)
	{
		/** from zero to hero e.g. BountyDashTargetPoints.Num() - 1 */
		short Spawner = FMath::Rand() % BountyDashTargetPoints.Num();

		/** from zero to hero again */
		short Obstical = FMath::Rand() % ObstaclesToSpawn.Num();

		float CapsuleOffset = 0.0f;

		FActorSpawnParameters SpawnInfo;

		/** Where to spawn Transform  */
		FTransform WhereToSpawnTransform = BountyDashTargetPoints[Spawner]->GetTransform();

		/** Adjust  Spawn Location according to SpawnPoint and Height */
		WhereToSpawnTransform.SetLocation(FVector(SpawnPoint, WhereToSpawnTransform.GetLocation().Y, WhereToSpawnTransform.GetLocation().Z + 25.f));
		
		if (ObstaclesToSpawn[Obstical])
		{
			AObstacle* NewObstacle = GetWorld()->SpawnActor<AObstacle>(ObstaclesToSpawn[Obstical], WhereToSpawnTransform, SpawnInfo);
			if (NewObstacle)
			{
				NewObstacle->SetKillPoint(KillPoint);

				USphereComponent* SpawnedObstacleSphereComponent = Cast<USphereComponent>(NewObstacle->GetComponentByClass(USphereComponent::StaticClass()));
				if (SpawnedObstacleSphereComponent)
				{
					/** lift the obstacle to Sphere Radius value  */
					NewObstacle->AddActorLocalOffset(FVector(0.0f, 0.0f, SpawnedObstacleSphereComponent->GetUnscaledSphereRadius()));
				}
			}
		}
	}
}

void AObstacleSpawner::FindFloorAndRetrieveData()
{
	TArray<AActor*> FoundFloorActors;
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

void AObstacleSpawner::FillTheSpawnTargetsArray()
{
	TArray<AActor*> FoundTargetPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABountyDashTargetPoint::StaticClass(), FoundTargetPointActors);

	for (auto Actor : FoundTargetPointActors)
	{
		ABountyDashTargetPoint* TestActor = Cast<ABountyDashTargetPoint>(Actor);
		if (TestActor)
		{
			BountyDashTargetPoints.AddUnique(TestActor);
		}
	}
}
