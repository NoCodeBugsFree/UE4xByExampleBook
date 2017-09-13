// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashGameMode.h"
#include "BountyDashCharacter.h"
#include "BountyDashHUD.h"
#include "Kismet/GameplayStatics.h"

ABountyDashGameMode::ABountyDashGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// set default pawn class to our ABountyDashCharacter
	DefaultPawnClass = ABountyDashCharacter::StaticClass();
	HUDClass = ABountyDashHUD::StaticClass();

	NumCoinsForSpeedIncrease = 5;
	GameSpeed = 10.0f;
	GameSpeedIncrease = 5.0f;
	GameLevel = 1;

	RunTime = 0.0f;
	bGameOver = false;
	StartGameOverCount = false;
	TimeTillGameOver = 2.0f;
	GameOverTimer = 0.0f;
}

void ABountyDashGameMode::CharacterScoreUp(int32 CharacterScore)
{
	if (CharacterScore != 0 && CharacterScore % NumCoinsForSpeedIncrease == 0)
	{
		GameSpeed += GameSpeedIncrease;
		GameLevel++;
	}
}

void ABountyDashGameMode::ReduceGameSpeed()
{
	if (GameSpeed > 10.0f)
	{
		GameSpeed -= GameSpeedIncrease;
		GameLevel--;
	}
}

void ABountyDashGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!StartGameOverCount)
	{
		RunTime += DeltaSeconds;
	}
	else
	{
		GameOverTimer += DeltaSeconds;
		if (GameOverTimer >= TimeTillGameOver)
		{
			bGameOver = true;
		}
	}
}

void ABountyDashGameMode::GameOver()
{
	StartGameOverCount = true;
}

void ABountyDashGameMode::SetGamePaused(bool gamePaused)
{
	UGameplayStatics::SetGamePaused(this, gamePaused);
}
