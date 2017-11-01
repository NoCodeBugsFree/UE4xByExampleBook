// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Ch6TargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ACh6TargetPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:

	/** returns next target point from our linked list  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	ACh6TargetPoint* GetNextTargetPoint() const { return NextTargetPoint; }
	
private:
	
	/** linked list imitation  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	ACh6TargetPoint* NextTargetPoint;
	
};
