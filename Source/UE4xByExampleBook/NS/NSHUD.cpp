// Fill out your copyright notice in the Description page of Project Settings.

#include "NSHUD.h"
#include "NSCharacter.h"
#include "NSGameState.h"
#include "NSGameMode.h"
#include "NSPlayerState.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

void ANSHUD::DrawHUD()
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
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor(1.f, 1.f, 1.f, 0.8f));
		TileItem.BlendMode = SE_BLEND_Translucent;

		Canvas->DrawItem(TileItem);

		ANSGameState* NSGameState = Cast<ANSGameState>(GetWorld()->GetGameState());
		if (NSGameState && NSGameState->IsInMenu())
		{
			int BlueScreenPosition = 50;
			int RedScreenPosition = Center.Y + 50;
			int nameSpacing = 25;
			int NumBlueteam = 1;
			int NumReadTeam = 1;

			FString ThisString = "BLUE TEAM:";
			DrawText(ThisString, FColor::Cyan, 50, BlueScreenPosition);
			ThisString = "RED TEAM:";
			DrawText(ThisString, FColor::Red, 50, RedScreenPosition);

			/** PlayerArray 
			Array of all PlayerStates, maintained on both server and clients (PlayerStates are always relevant) 
			UPROPERTY(Transient, BlueprintReadOnly, Category = GameState)
			TArray<APlayerState*> PlayerArray;
			*/
			for (auto player : NSGameState->PlayerArray)
			{
				ANSPlayerState* NSPlayerState = Cast<ANSPlayerState>(player);
				if (NSPlayerState)
				{
					if (NSPlayerState->GetTeam() == ETeam::BLUE_TEAM)
					{
						ThisString = FString::Printf(TEXT("%s"), &(NSPlayerState->PlayerName[0]));
						DrawText(ThisString, FColor::Cyan, 50, BlueScreenPosition + nameSpacing * NumBlueteam);
						NumBlueteam++;
					}
					else
					{
						ThisString = FString::Printf(TEXT("%s"), &(NSPlayerState->PlayerName[0]));
						DrawText(ThisString, FColor::Red, 50, RedScreenPosition + nameSpacing * NumReadTeam);
						NumReadTeam++;
					}
				}
			}

			if (GetWorld()->GetAuthGameMode())
			{
				ThisString = "Press R to start game";
				DrawText(ThisString, FColor::Yellow, Center.X, Center.Y);
			}
			else
			{
				ThisString = "Waiting on Server!!";
				DrawText(ThisString, FColor::Yellow, Center.X, Center.Y);
			}
		}
		else
		{
			if (ANSCharacter* NSCharacter = Cast<ANSCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
			{
				if (NSCharacter->GetNSPlayerState())
				{
					FString HUDString = FString::Printf(
						TEXT("Health: %f, Score: %f, Deaths : %d"),
						NSCharacter->GetNSPlayerState()->GetHealth(),
						NSCharacter->GetNSPlayerState()->Score,
						NSCharacter->GetNSPlayerState()->GetDeaths());

					DrawText(HUDString, FColor::Yellow, 50, 50);
				}
			}
		}
	} // if (Canvas)
}
