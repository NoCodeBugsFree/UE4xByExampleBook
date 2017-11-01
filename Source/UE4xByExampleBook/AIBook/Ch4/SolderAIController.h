// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SolderAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ASolderAIController : public AAIController
{
	GENERATED_BODY()

public:



protected:

	void Possess(APawn* Pawn) override;

	void Tick(float DeltaSeconds) override;

private:
	
	/** Patrol Points for our AI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class AWayPoint*> PatrolPoints;

	/** next patrol point to move  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 NextPatrolPointNumber = 0;

	/** sets the NextPatrolPointNumber to random PP from PatrolPoints array  */
	void ResetCanChangePP();

	bool bCanChangePP = true;
	
};
