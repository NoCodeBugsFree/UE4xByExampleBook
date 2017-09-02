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
	PrimaryActorTick.bCanEverTick = true;

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
	
	/** fill the SpawnTransforms array  */
	FillSpawnTransforms();
	
	/** find floor actor and initialize variables  */
	FindFloorAndInitVariables();
	
	// Create Timers
	SetTimers();
}

void ACoinSpawner::SetTimers()
{
	FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();
	worldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
	worldTimeManager.SetTimer(SpawnMoveTimerHandle, this, &ACoinSpawner::MoveSpawner, MovementTimeInterval, true);
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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABountyDashTargetPoint::StaticClass(),
		FoundActors);

	for (auto Actor : FoundActors)
	{
		ABountyDashTargetPoint* TestActor = Cast<ABountyDashTargetPoint>(Actor);
		if (TestActor)
		{
			SpawnTransforms.AddUnique(TestActor);
		}
	}
}

// Called every frame
void ACoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		FActorSpawnParameters spawnParams;

		FTransform coinTransform = SpawnTransforms[TargetLoc]->GetTransform();

		coinTransform.SetLocation(FVector(SpawnPoint, coinTransform.GetLocation().Y, coinTransform.GetLocation().Z));
		ACoin* spawnedCoin = GetWorld()->SpawnActor<ACoin>(CoinObject, coinTransform, spawnParams);
		if (spawnedCoin)
		{
			USphereComponent* coinSphere = Cast<USphereComponent>(spawnedCoin->GetComponentByClass(USphereComponent::StaticClass()));
			if (coinSphere)
			{
				float offset = coinSphere->GetUnscaledSphereRadius();
				spawnedCoin->AddActorLocalOffset(FVector(0.0f, 0.0f, offset));
			}
			NumCoinsToSpawn--;
		}
		if (NumCoinsToSpawn <= 0)
		{
			FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();
			worldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
			worldTimeManager.ClearTimer(CoinTimerHandle);
		}
	}
}

void ACoinSpawner::SpawnPowerUp()
{
	FActorSpawnParameters SpawnInfo;
	FTransform myTrans = SpawnTransforms[TargetLoc]->GetTransform();
	myTrans.SetLocation(FVector(SpawnPoint,myTrans.GetLocation().Y, myTrans.GetLocation().Z));
	ABountyDashPowerUp* newObs = GetWorld()->SpawnActor<ABountyDashPowerUp>(PowerUpObject, myTrans, SpawnInfo);
	if (newObs)
	{
		newObs->SetKillPoint(KillPoint);
		USphereComponent* powerUpSphere = Cast<USphereComponent>(newObs->GetComponentByClass(USphereComponent::StaticClass()));
		if (powerUpSphere)
		{
			float offset = powerUpSphere->GetUnscaledSphereRadius();
			newObs->AddActorLocalOffset(FVector(0.0f, 0.0f, offset));
		}
	}
}


void ACoinSpawner::SpawnCoinSet()
{
	NumCoinsToSpawn = FMath::RandRange(MinSetCoins, MaxSetCoins);
	FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();

	// Swap active timers
	worldTimeManager.ClearTimer(CoinSetTimerHandle);
	worldTimeManager.SetTimer(CoinTimerHandle, this, &ACoinSpawner::SpawnCoin, CoinTimeInterval, true);
}

void ACoinSpawner::MoveSpawner()
{
	/** FMath::Rand() Returns a random integer between 0 and RAND_MAX, inclusive */
	TargetLoc = FMath::Rand() % SpawnTransforms.Num();
}