// Fill out your copyright notice in the Description page of Project Settings.
#include "ScriptingCookbookGameMode.h"
#include "UE4xByExampleBook.h"
#include "ScriptingCookbook/Ch7/SingleInterfaceActor.h"
#include "EngineUtils.h"
#include "ScriptingCookbook/Ch10/CookbookStyle.h"
#include "Landscape.h"
#include "LandscapeInfo.h"
#include "ScriptingCookbook/Ch12/Noise1234.h"


void AScriptingCookbookGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	/** ToggleHUD demo */
	// ToggleHUD();

	/** Click Event to button */
	// BindClickEvent();

	/**  Use Data Binding with Unreal Motion Graphics */
	// DataBinding();

	/** Controlling widget appearance with Styles  */
	// Style();

}

void AScriptingCookbookGameMode::Style()
{
	FCookbookStyle::Initialize();

	Widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.ButtonStyle(FCookbookStyle::Get(), "NormalButtonBrush")
		.ContentPadding(FMargin(16))
		.Content()
		[
			SNew(STextBlock)
			.TextStyle(FCookbookStyle::Get(), "NormalButtonText").Text(FText::FromString("Styled Button"))
		]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef(), 1);
}

void AScriptingCookbookGameMode::DataBinding()
{
	Widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Content()
		[
			SNew(STextBlock)
			.Text(TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateUObject(this, &AScriptingCookbookGameMode::GetButtonLabel)))
		]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef(), 1);
}

void AScriptingCookbookGameMode::BindClickEvent()
{
	Widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.OnClicked(FOnClicked::CreateUObject(this, &AScriptingCookbookGameMode::ButtonClicked))
		.Content()
		[
			SAssignNew(ButtonLabel, STextBlock)
			.Text(FText::FromString(TEXT("Click me!")))
		]
		];
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef(), 1);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GEngine->GetFirstLocalPlayerController(GetWorld())->SetInputMode(FInputModeUIOnly().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock).SetWidgetToFocus(Widget));
}

void AScriptingCookbookGameMode::ToggleHUD()
{
	widget = SNew(SVerticalBox)
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
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), widget.ToSharedRef(), 1);

	GetWorld()->GetTimerManager().SetTimer(HUDToggleTimer,
		FTimerDelegate::CreateLambda
		([this] {
		if (this->widget->GetVisibility().IsVisible())
		{
			this->widget->SetVisibility(EVisibility::Hidden);
		}
		else
		{
			this->widget->SetVisibility(EVisibility::Visible);
		}
	}), 1.f, true);
}

void AScriptingCookbookGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(HUDToggleTimer);
}

FReply AScriptingCookbookGameMode::ButtonClicked()
{
	ButtonLabel->SetText(FString(TEXT("Clicked!")));
	return FReply::Handled();
}

FText AScriptingCookbookGameMode::GetButtonLabel() const
{
	FVector ActorLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return FText::FromString(FString::Printf(TEXT("%f, %f, %f"), ActorLocation.X, ActorLocation.Y, ActorLocation.Z));
}
