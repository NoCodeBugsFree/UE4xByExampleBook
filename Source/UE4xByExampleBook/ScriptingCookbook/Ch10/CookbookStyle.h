// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class FCookbookStyle
{

public:

	static void Initialize();
	static void Shutdown();
	static void ReloadTextures();
	static const ISlateStyle& Get();
	static FName GetStyleSetName();

	static TSharedPtr<class FSlateStyleSet> CookbookStyleInstance;

private:

	static TSharedRef<class FSlateStyleSet> Create();

private:
	
};
