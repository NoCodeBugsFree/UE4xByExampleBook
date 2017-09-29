// Fill out your copyright notice in the Description page of Project Settings.

#include "VSHUDWidget.h"
#include "VSCharacter.h"


void UVSHUDWidget::UpdateHUD()
{
	if (WidgetOwnerVSCharacter)
	{
		/** retrieve all data from owner character  */
		WidgetOwnerVSCharacter->GetDataForHUD(AmmoText, TargetsText, HealthBarPercentage, StaminaBarPercentage, RoundText);
	}
}

void UVSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/** sets owner reference  */
	WidgetOwnerVSCharacter = Cast<AVSCharacter>(GetOwningPlayerPawn());

}

void UVSHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	UpdateHUD();
}
