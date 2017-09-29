// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VSHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UVSHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	
	/** call in NativeTick function to update HUD to valid state  */
	void UpdateHUD();
	
	/** calls when widget is constructed  */
	virtual void NativeConstruct() override;
	
	/** call every frame  */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	/** widget owner character reference  */
	class AVSCharacter* WidgetOwnerVSCharacter;

	/** round text  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FText RoundText;
	
	/** ammo text  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FText AmmoText;

	/** targets text  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FText TargetsText;
	
	/** health bar percentage  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float HealthBarPercentage;

	/** stamina bar percentage  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float StaminaBarPercentage;
};