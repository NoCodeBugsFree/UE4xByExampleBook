// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BountyDashObject.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ACoin : public ABountyDashObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	
	/** Shows whether the character is magnet or not */
	bool bIsBeingPulled;

protected:

	ACoin();

	void Tick(float DeltaSeconds) override;

	/** Calls to handle character colliding  */
	void CollideWithCharacter(AActor* OtherActor);

	/** Calls to handle obstacle colliding  */
	void LiftCollidingCoin(AActor* OtherActor);

	/** Bounty Dash Particles Template  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	TSubclassOf<class ABountyDashParticle> BountyDashParticlesToSpawn;
	
private:

	/** Represents Coin Mesh  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CoinMesh;
	
};
