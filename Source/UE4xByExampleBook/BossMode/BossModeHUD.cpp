// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeHUD.h"
#include "Engine/Canvas.h"

void ABossModeHUD::DrawHUD()
{
	Super::DrawHUD();

	if (Canvas)
	{
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		
		// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		FVector2D CrosshairDrawPosition;
		if (CrosshairTexture)
		{
			CrosshairDrawPosition.X = Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5);
			CrosshairDrawPosition.Y = Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f);
		}
		
		// draw the Crosshair
		// FCanvasTileItem - 'Tile' item can override size and UV 
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor(1.f, 1.f, 1.f, 0.5f));
		TileItem.BlendMode = SE_BLEND_Translucent;

		Canvas->DrawItem(TileItem);
	}
}
