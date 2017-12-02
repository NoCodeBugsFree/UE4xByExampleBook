// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barracks.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABarracks : public AActor
{
	GENERATED_BODY()
	
	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BuildingMesh;
	
	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* SpawnPoint;

public:	
	

protected:

	// Sets default values for this actor's properties
	ABarracks();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// -----------------------------------------------------------------------------------

	/**  template  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABarracksUnit> UnitToSpawn;

	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float SpawnInterval = 10.f;

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SpawnUnit();
	
	/**   */
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	
public:	
	
	
	
};
