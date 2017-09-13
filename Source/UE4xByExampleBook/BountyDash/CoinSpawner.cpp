// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinSpawner.h"
#include "Components/SceneComponent.h"
#include "BountyDashTargetPoint.h"
#include "Coin.h"
#include "Floor.h"
#include "CoinSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "BountyDashPowerUp.h"

// Sets default values
ACoinSpawner::ACoinSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MaxSetCoins = 5;
	MinSetCoins = 3;
	CoinSetTimeInterval = 4.0f;
	CoinTimeInterval = 0.5f;
	MovementTimeInterval = 1.0f;
}

void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	/** Fill the SpawnTransforms array  */
	FillSpawnTransforms();
	
	/** Find floor actor and initialize variables  */
	FindFloorAndInitVariables();
	
	// Create Timers
	SetTimers();
}

void ACoinSpawner::SetTimers()
{
	FTimerManager& WorldTimeManager = GetWorld()->GetTimerManager();
	WorldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
	WorldTimeManager.SetTimer(SpawnMoveTimerHandle, this, &ACoinSpawner::MoveSpawner, MovementTimeInterval, true);
}

void ACoinSpawner::FindFloorAndInitVariables()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFloor::StaticClass(), FoundActors);
	TArray<AFloor*> FloorActors;

	for (auto Actor : FoundActors)
	{
		AFloor* TestActor = Cast<AFloor>(Actor);
		if (TestActor)
		{
			FloorActors.AddUnique(TestActor);
		}
	}

	if (FloorActors.Num() > 1)
	{
		UE_LOG(LogTemp, Error, TEXT("FloorActors.Num() > 1 !!!"));
		return;
	}
	else
	{
		if (FloorActors.IsValidIndex(0))
		{
			if (FloorActors[0]->GetWorld() == GetWorld())
			{
				KillPoint = FloorActors[0]->GetKillPoint();
				SpawnPoint = FloorActors[0]->GetSpawnPoint();
			}
		}
	}
}

void ACoinSpawner::FillSpawnTransforms()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABountyDashTargetPoint::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ABountyDashTargetPoint* TestActor = Cast<ABountyDashTargetPoint>(Actor);
		if (TestActor)
		{
			SpawnTransforms.AddUnique(TestActor);
		}
	}
}

void ACoinSpawner::SpawnCoin()
{
	if (FMath::Rand() % 100 < PowerUpChance)
	{
		SpawnPowerUp();
		NumCoinsToSpawn--;
	} 
	else
	{
		FActorSpawnParameters SpawnParams;

		FTransform CoinTransform = SpawnTransforms[TargetLocation]->GetTransform();

		/** Adjust spawn location  */
		CoinTransform.SetLocation(FVector(SpawnPoint, CoinTransform.GetLocation().Y, CoinTransform.GetLocation().Z));

		ACoin* NewCoin = GetWorld()->SpawnActor<ACoin>(CoinObject, CoinTransform, SpawnParams);
		if (NewCoin)
		{
			USphereComponent* CoinSphereComponent = Cast<USphereComponent>(NewCoin->GetComponentByClass(USphereComponent::StaticClass()));
			if (CoinSphereComponent)
			{
				float ZOffset = CoinSphereComponent->GetUnscaledSphereRadius();
				NewCoin->AddActorLocalOffset(FVector(0.0f, 0.0f, ZOffset));
			}
			NumCoinsToSpawn--;
		}
		if (NumCoinsToSpawn <= 0)
		{
			FTimerManager& WorldTimeManager = GetWorld()->GetTimerManager();
			WorldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
			WorldTimeManager.ClearTimer(CoinTimerHandle);
		}
	}
}

void ACoinSpawner::SpawnPowerUp()
{
	FActorSpawnParameters SpawnParams;
	FTransform SpawnTransform = SpawnTransforms[TargetLocation]->GetTransform();

	/**  Adjust spawn location  */
	SpawnTransform.SetLocation(FVector(SpawnPoint,SpawnTransform.GetLocation().Y, SpawnTransform.GetLocation().Z));

	ABountyDashPowerUp* NewPowerUp = GetWorld()->SpawnActor<ABountyDashPowerUp>(PowerUpObject, SpawnTransform, SpawnParams);
	if (NewPowerUp)
	{
		NewPowerUp->SetKillPoint(KillPoint);
		USphereComponent* PowerUpSphereComponent = Cast<USphereComponent>(NewPowerUp->GetComponentByClass(USphereComponent::StaticClass()));
		if (PowerUpSphereComponent)
		{
			float ZOffset = PowerUpSphereComponent->GetUnscaledSphereRadius();
			NewPowerUp->AddActorLocalOffset(FVector(0.0f, 0.0f, ZOffset));
		}
	}
}

void ACoinSpawner::SpawnCoinSet()
{
	NumCoinsToSpawn = FMath::RandRange(MinSetCoins, MaxSetCoins);
	FTimerManager& WorldTimeManager = GetWorld()->GetTimerManager();

	// Swap active timers
	WorldTimeManager.ClearTimer(CoinSetTimerHandle);
	WorldTimeManager.SetTimer(CoinTimerHandle, this, &ACoinSpawner::SpawnCoin, CoinTimeInterval, true);
}

void ACoinSpawner::MoveSpawner()
{
	/** FMath::Rand() Returns a random integer between 0 and RAND_MAX, inclusive */
	TargetLocation = FMath::Rand() % SpawnTransforms.Num();
}