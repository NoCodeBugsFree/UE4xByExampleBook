// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryActor.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AInventoryActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	virtual void PickUp();

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	virtual void PutDown(FTransform TargetLocation);
	
protected:
	
	AInventoryActor();

private:
	
	
};
