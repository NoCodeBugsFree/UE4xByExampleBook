// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BountyDashObject.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABountyDashObject : public AActor
{
	GENERATED_BODY()
	
public:	
	
	/** Sets the KillPoint  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetKillPoint(float NewKillPoint) { KillPoint = NewKillPoint; }

	/** Returns the KillPoint */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetKillPoint() const { return KillPoint; }

protected:

	// Sets default values for this actor's properties
	ABountyDashObject();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	virtual void MyOnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	/** Sphere Collision Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Collider;

private:

	/** Game Mode Reference  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ABountyDashGameMode* BountyDashGameMode;
	
	/** Destroy point for this object  */
	float KillPoint = -20000.0f;

};
