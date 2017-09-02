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

	/** Test  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	EPowerUp Type = EPowerUp::MAGNET;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	virtual void MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPowerUpObject* PowerUp;
	
};
