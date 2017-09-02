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
	
public:

	ABountyDashParticle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* particleSystem;

protected:



private:
	
	
};
