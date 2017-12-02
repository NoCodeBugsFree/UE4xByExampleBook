// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Peasant.generated.h"

UENUM(BlueprintType)
enum class EBodyColor : uint8
{
	BC_Green UMETA(DisplayName = "Green"),
	BC_Yellow UMETA(DisplayName = "Yellow"),
	BC_Gray UMETA(DisplayName = "Gray"),
	BC_Black UMETA(DisplayName = "Black"),
	// EN_Green = 250 UMETA(DisplayName = "Green"),
};

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API APeasant : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	
	APeasant();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, category = Peasant)
	void Flee(AKing* DeadKing);

protected:

	

private:
	
	
};
