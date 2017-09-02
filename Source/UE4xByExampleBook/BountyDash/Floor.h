// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AFloor();

	float GetKillPoint();

	float GetSpawnPoint();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<USceneComponent*> FloorMeshScenes;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> FloorMeshes;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;

	int32 NumRepeatingMesh;

	float KillPoint;

	float SpawnPoint;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ABountyDashGameMode* BountyDashGameMode;

public:	
	

	
	
};
