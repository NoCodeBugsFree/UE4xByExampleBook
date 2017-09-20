// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSGameMode.h"
#include "NSSpawnPoint.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ANSSpawnPoint : public AActor
{
	GENERATED_BODY()
	
protected:

	// Sets default values for this actor's properties
	ANSSpawnPoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** sets the capsule color  */
	virtual void OnConstruction(const FTransform& Transform) override;
	
	/** overlap begins. check if we have not OtherActor in our OverlappingActors array - add it into the array  */
	UFUNCTION()
	void ActorBeginOverlaps(AActor* OverlapedActor, AActor* OtherActor);
	
	/** overlap ends. if we have not OtherActor in the OverlappingActors array - remove it from the array   */
	UFUNCTION()
	void ActorEndOverlaps(AActor* OverlapedActor, AActor* OtherActor);

	/** holds the current team of the spawn point  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETeam Team;

private:

	/** represents spawn capsule  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* SpawnCapsule;

	/** Actors that overlaps this one */
	TArray<class AActor*> OverlappingActors;

public:	
	
	/** Returns current team  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	ETeam GetTeam() const { return Team; }

	/** Returns whether or not this actor is overlapped  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	bool GetBlocked() const { return OverlappingActors.Num() != 0; };
	
};
