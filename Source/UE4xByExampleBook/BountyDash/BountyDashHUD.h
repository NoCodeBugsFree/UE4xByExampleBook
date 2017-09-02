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
	
	ABountyDashHUD();

	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	// -----------------------------------------------------------------------------------

	class ABountyDashCharacter* BountyDashCharacter;

	class ABountyDashGameMode* BountyDashGameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UFont* HUDFont;
	
};
