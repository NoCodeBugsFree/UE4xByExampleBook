// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_EnemyPursue.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AAIController_EnemyPursue : public AAIController
{
	GENERATED_BODY()

private:

	AAIController_EnemyPursue();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	APawn* TargetPawn;
};
