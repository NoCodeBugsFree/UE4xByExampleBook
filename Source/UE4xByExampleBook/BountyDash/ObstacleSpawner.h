// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
protected:

	// Sets default values for this actor's properties
	AObstacleSpawner();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	/** Spawns the obstacle  */
	void SpawnObstacle();

public:	
	
	/** Templates for what to spawn  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AObstacle>> ObstaclesToSpawn;

	/** Target Points  */
	UPROPERTY()
	TArray<class ABountyDashTargetPoint*> BountyDashTargetPoints;

	/** Silly timer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTimer = 1.5f;

	/** Root  */
	UPROPERTY()
	class USceneComponent* Scene;

private:

	/** Find the floor and retrieve corresponding data */
	void FindFloorAndRetrieveData();

	/** Fill the SpawnTargets   */
	void FillTheSpawnTargetsArray();

	// -----------------------------------------------------------------------------------

	/** Game Mode Reference  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ABountyDashGameMode* BountyDashGameMode;

	/** Potential Floors in the World. Intended once instance of floor. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class AFloor*> Floors;

	/** Kill Point for spawned object */
	float KillPoint;

	/**  Spawn Point for spawned object */
	float SpawnPoint;

	/** Time from last spawn  */
	float TimeSinceLastSpawn;
	
};
