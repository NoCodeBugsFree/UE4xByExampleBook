// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_RandomMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AAIController_RandomMoveTo : public AAIController
{
	GENERATED_BODY()
	
private:

	void Possess(APawn* Pawn) override;

	/** calls every second to move AI to random point  */
	void MoveToNextRandomPoint();
	
};
