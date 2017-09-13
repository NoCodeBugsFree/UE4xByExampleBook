// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinSpawner.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ACoinSpawner : public AActor
{
	GENERATED_BODY()
		
protected:

	// Sets default values for this actor's properties
	ACoinSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	/** Starts timer  */
	void SetTimers();

	/** Finds floor actor (intended one instance in the World) and initialize KillPoint and SpawnPoint  */
	void FindFloorAndInitVariables();
	
	/** Finds all BountyDashTargetPoint and stores them into the array */
	void FillSpawnTransforms();

	/** SpawnCoin or SpawnPowerUp depending on PowerUpChance */
	void SpawnCoin();

	/**  Spawn required amount of coins (NumCoinsToSpawn)  each specified interval (CoinTimeInterval) */
	void SpawnCoinSet();

	/** Pick the next spawner point (TargetLocation) */
	void MoveSpawner();

	/** Spawns PowerUp Object  */
	void SpawnPowerUp();

	// -----------------------------------------------------------------------------------

	/** Spawn Transforms actors  */
	UPROPERTY()
	TArray<class ABountyDashTargetPoint*> SpawnTransforms;

	/** Maximum amount of coins to spawn  */
	UPROPERTY(EditAnywhere)
	int32 MaxSetCoins = 5;

	/** Minimum amount of coins to spawn  */
	UPROPERTY(EditAnywhere)
	int32 MinSetCoins = 3;

	/**  Timer delay for spawn coins Sets */
	UPROPERTY(EditAnywhere)
	float CoinSetTimeInterval = 4.f;

	/** Timer delay for spawn each coin  */
	UPROPERTY(EditAnywhere)
	float CoinTimeInterval = 0.5f;

	/**  delay to move spawner */
	UPROPERTY(EditAnywhere)
	float MovementTimeInterval = 1.f;

	/** Chance to spawn PowerUp object */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	int32 PowerUpChance = 20;
	
	/** Current amount of coins to spawn  */
	int32 NumCoinsToSpawn;
	
	/** Kill Point value to set in spawned actors */
	float KillPoint;

	/** Spawn Point value to set in spawned actors */
	float SpawnPoint;

	/** Current spawn location  */
	int32 TargetLocation;

	/** Coin set spawn timer  */
	FTimerHandle CoinSetTimerHandle;

	/** Each coin spawn timer  */
	FTimerHandle CoinTimerHandle;

	/** Move spawn point timer  */
	FTimerHandle SpawnMoveTimerHandle;

	/** Coin To Spawn Template  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACoin> CoinObject;

	/** Root  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	/** PowerUp Object To Spawn Template */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABountyDashPowerUp> PowerUpObject;
	
};
