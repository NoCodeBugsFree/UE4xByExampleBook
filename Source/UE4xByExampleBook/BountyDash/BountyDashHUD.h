// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BountyDashHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ABountyDashHUD : public AHUD
{
	GENERATED_BODY()
	
private:

	void BeginPlay() override;

	/** Calls every tick to draw actual HUD  */
	void DrawHUD() override;

	// -----------------------------------------------------------------------------------

	/** Character reference  */
	class ABountyDashCharacter* BountyDashCharacter;

	/** Game Mode Reference  */
	class ABountyDashGameMode* BountyDashGameMode;
	
	/** Font template  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UFont* HUDFont;
	
};
