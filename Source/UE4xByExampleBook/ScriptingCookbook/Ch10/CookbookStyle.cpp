// Fill out your copyright notice in the Description page of Project Settings.

#include "CookbookStyle.h"
#include "CookbookStyle.h"
#include "SlateGameResources.h"

void FCookbookStyle::Initialize()
{
	UE_LOG(LogTemp, Error, TEXT("FCookbookStyle::Initialize()"));
	if (!CookbookStyleInstance.IsValid())
	{
		
		CookbookStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*CookbookStyleInstance);
	}
}

void FCookbookStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*CookbookStyleInstance);
	ensure(CookbookStyleInstance.IsUnique());
	CookbookStyleInstance.Reset();
}

FName FCookbookStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CookbookStyle"));
	return StyleSetName;
}

// FPaths::ProjectContentDir()
#define IMAGE_BRUSH(RelativePath, ... ) FSlateImageBrush(FPaths::ProjectContentDir() / "Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)
#define BOX_BRUSH(RelativePath, ... ) FSlateBoxBrush(FPaths::ProjectContentDir() / "Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)
#define BORDER_BRUSH(RelativePath, ... ) FSlateBorderBrush(FPaths::ProjectContentDir() / "Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)
#define TTF_FONT(RelativePath, ... ) FSlateFontInfo(FPaths::ProjectContentDir() / "Slate" / RelativePath + TEXT(".ttf"), __VA_ARGS__)
#define OTF_FONT(RelativePath, ... ) FSlateFontInfo(FPaths::ProjectContentDir() / "Slate" / RelativePath + TEXT(".otf"), __VA_ARGS__)

TSharedRef<class FSlateStyleSet> FCookbookStyle::Create()
{
	TSharedRef<FSlateStyleSet>StyleRef = FSlateGameResources::New(FCookbookStyle::GetStyleSetName(), "/Game/Slate", "/Game/Slate");
	FSlateStyleSet& Style = StyleRef.Get();
	Style.Set("NormalButtonBrush", FButtonStyle(). SetNormal(BOX_BRUSH("Button", FVector2D(54, 54), FMargin(14.0f / 54.0f))));
	Style.Set("NormalButtonText", FTextBlockStyle(FTextBlockStyle::GetDefault()).SetColorAndOpacity(FSlateColor(FLinearColor(1, 1, 1, 1))));
	return StyleRef;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

TSharedPtr<class FSlateStyleSet> FCookbookStyle::CookbookStyleInstance = nullptr;

void FCookbookStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FCookbookStyle::Get()
{
	return *CookbookStyleInstance;
}