// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UVSSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	/** calls to clear save game object  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Reset() { CurrentRound = 1; }

	/** current round value  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentRound = 1;
	
	
};
