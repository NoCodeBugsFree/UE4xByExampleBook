// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_AvoidObstacles.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AAIController_AvoidObstacles : public AAIController
{
	GENERATED_BODY()

private:
	
	/** change turn direction every 2 seconds  */
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	// -----------------------------------------------------------------------------------
	
	/** simple reverse bool flag  */
	void InverseShouldTurnRight();

	bool bShouldTurnRight = true;

	bool bCanRotateBackwards = true;
	
	void RotateBackwards();
	
};
