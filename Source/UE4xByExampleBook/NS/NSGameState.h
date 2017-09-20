// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NSGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ANSGameState : public AGameState
{
	GENERATED_BODY()
	
private:
	
	/** Returns properties that are replicated for the lifetime of the actor channel */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
	/**  flag that will inform the player's HUD if the game is still in the menu, and yet to be run by the server.  */
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsInMenu = false;

public:
	
	/** Returns bInMenu state   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	bool IsInMenu() const { return bIsInMenu; }

	/** Setter for bIsInMenu state   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetIsInMenu(bool NewIsInMenu) { bIsInMenu = NewIsInMenu; }
	
};
