// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomHUDPlayerController.h"
#include "SlateBasics.h"
#include "SButton.h"
#include "STextBlock.h"

void ACustomHUDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/** create a simple button and add it to a viewport  */

	TSharedRef<SVerticalBox> widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Test button")))
		]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), widget, 1);
}
