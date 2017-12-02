// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "King.generated.h"

/** declare  */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKingDeathSignature, AKing*, King);

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AKing : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AKing();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = King)
	void Die();

	UPROPERTY(BlueprintAssignable)
	FOnKingDeathSignature OnKingDeath;

};
