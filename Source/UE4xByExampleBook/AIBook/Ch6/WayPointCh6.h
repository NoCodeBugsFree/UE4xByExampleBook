// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "WayPointCh6.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AWayPointCh6 : public ATargetPoint
{
	GENERATED_BODY()
	
public:

	/** return next way point  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	AWayPointCh6* GetNextWayPoint() const { return NextWayPoint; }
	
private:

	/** Next Way Point  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	AWayPointCh6* NextWayPoint;

};
