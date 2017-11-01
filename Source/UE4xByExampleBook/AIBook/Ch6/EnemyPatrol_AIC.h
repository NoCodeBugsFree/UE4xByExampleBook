// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyPatrol_AIC.generated.h"

/**
 * 
 */



UCLASS()
class UE4XBYEXAMPLEBOOK_API AEnemyPatrol_AIC : public AAIController
{
	GENERATED_BODY()
	
public:

	

protected:

	void Possess(APawn* Pawn) override;

	void Tick(float DeltaSeconds) override;

	/** sets current way point to random way point from the way points array  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetNextWayPoint();
	
	/** calls to fill the way points array  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void FillWayPoints();
	
private:

	/** Possessed Pawn reference  */
	class AEnemyPatrolCharacter* EnemyPatrolCharacter;
	
	/** all available Way Points  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class AWayPointCh6*> WayPoints;
	
	/** Current Way Point  */
	class AWayPointCh6* CurrentWayPoint;
};
