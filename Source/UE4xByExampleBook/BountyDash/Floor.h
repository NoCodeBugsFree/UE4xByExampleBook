// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AFloor : public AActor
{
	GENERATED_BODY()
	
protected:

	// Sets default values for this actor's properties
	AFloor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** 80 Scenes  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	TArray<USceneComponent*> FloorMeshScenes;

	/** 80 Meshes  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	TArray<UStaticMeshComponent*> FloorMeshes;

	/** Destroyed Floor Piece Template to spawn wall of death  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (BlueprintProtected = "true"))
	TSubclassOf<class ADestroyedFloorPiece> DestroyedFloorPieceTemplate;


	/** The reason we are using a BoxComponent 
	 * instead of the meshes for collision is that we do not want the player
	 * to translate with the moving meshes. Due to surface friction simulation, having the
	 * character collide with any of the moving meshes will cause the player to move with
	 * the mesh. 
	 */ 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	class UBoxComponent* CollisionBox;

	/** Determines how many meshes we will have in the chain.  */
	int32 NumRepeatingMesh = 80;

	/** to save output calculations from the constructor so we may use it in the Tick() function.  */
	float KillPoint;

	/** to save output calculations from the constructor so we may use it in the Tick() function.  */
	float SpawnPoint;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ABountyDashGameMode* BountyDashGameMode;

public:	

	/** Returns Kill Point  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetKillPoint() const { return KillPoint; }

	/** Returns Spawn Point  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetSpawnPoint() const { return SpawnPoint; }
	
	
};
