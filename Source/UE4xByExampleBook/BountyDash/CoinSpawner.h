// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinSpawner.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ACoinSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACoin> CoinObject;

	UPROPERTY()
	TArray<class ABountyDashTargetPoint*> SpawnTransforms;

	UPROPERTY()
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	int32 MaxSetCoins;

	UPROPERTY(EditAnywhere)
	int32 MinSetCoins;

	UPROPERTY(EditAnywhere)
	float CoinSetTimeInterval;

	UPROPERTY(EditAnywhere)
	float CoinTimeInterval;

	UPROPERTY(EditAnywhere)
	float MovementTimeInterval;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABountyDashPowerUp> PowerUpObject;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	int32 PowerUpChance = 20;

	void SpawnPowerUp();

protected:

	// Sets default values for this actor's properties
	ACoinSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetTimers();

	void FindFloorAndInitVariables();

	void FillSpawnTransforms();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnCoin();

	void SpawnCoinSet();

	void MoveSpawner();

	int32 NumCoinsToSpawn;

	float KillPoint;

	float SpawnPoint;

	int32 TargetLoc;

	FTimerHandle CoinSetTimerHandle;

	FTimerHandle CoinTimerHandle;

	FTimerHandle SpawnMoveTimerHandle;
	
public:	
	

	
	
};
