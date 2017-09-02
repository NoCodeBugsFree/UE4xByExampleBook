// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashHUD.h"
#include "BountyDashCharacter.h"
#include "BountyDashGameMode.h"

ABountyDashHUD::ABountyDashHUD()
{

}

void ABountyDashHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode());
		BountyDashCharacter = Cast<ABountyDashCharacter>(GetOwningPawn());
	}

}

void ABountyDashHUD::DrawHUD()
{
	Super::DrawHUD();
	
	if (BountyDashCharacter && BountyDashGameMode)
	{
		if (BountyDashGameMode->GetGameOver())
		{
			DrawText(TEXT("GAME OVER!!! Press R to Restart!"), FColor::Red, 300.f, 200.f, HUDFont);
			BountyDashGameMode->SetGamePaused(true);
			return;
		}

		int32 Score = BountyDashCharacter->GetScore();
		float RunTime = BountyDashGameMode->GetRunTime();
		FString HUDString = FString::Printf(TEXT("Score: %d RunTime: %.1f"), Score, RunTime);
		DrawText(HUDString, FColor::Orange, 50.f, 50.f, HUDFont);
	}
}
