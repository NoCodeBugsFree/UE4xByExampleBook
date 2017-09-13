// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BountyDash/BountyDashObject.h"
#include "PowerUpObject.h"
#include "BountyDashPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ABountyDashPowerUp : public ABountyDashObject
{
	GENERATED_BODY()

public:

	ABountyDashPowerUp();

	/** PowerUp Type  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	EPowerUp PowerUpType = EPowerUp::MAGNET;

protected:

	/** PowerUp Static Mesh  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PowerUpMesh;

	UFUNCTION()
	virtual void MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

private:
	
	/** PowerUp Object  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPowerUpObject* PowerUp;
	
};
