// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BountyDash/BountyDashObject.h"
#include "BountyDashParticle.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ABountyDashParticle : public ABountyDashObject
{
	GENERATED_BODY()
	
private:

	ABountyDashParticle();

	/** Particle System Component   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleSystemComponent;
	
};
