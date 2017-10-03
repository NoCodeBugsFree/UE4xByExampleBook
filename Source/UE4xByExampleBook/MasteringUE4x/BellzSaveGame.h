// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BellzSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UBellzSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	
	UBellzSaveGame();

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	FString SlotName = "CoinsSaveSlot";

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	uint32 PlayerIndex = 0;

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	uint32 CollectedCoins;

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	float PlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	uint32 LastUsedWeaponIndex;

	UPROPERTY(VisibleAnywhere, Category = SavedValues)
	FString PlayerName;

};
