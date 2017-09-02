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
	startGameOverCount = false;
	timeTillGameOver = 2.0f;
	gameOverTimer = 0.0f;
}

void ABountyDashGameMode::CharScoreUp(unsigned int CharScore)
{
	if (CharScore != 0 && CharScore % NumCoinsForSpeedIncrease == 0)
	{
		GameSpeed += GameSpeedIncrease;
		GameLevel++;
	}
}

float ABountyDashGameMode::GetInvGameSpeed()
{
	return -GameSpeed;
}

float ABountyDashGameMode::GetGameSpeed()
{
	return GameSpeed;
}

int32 ABountyDashGameMode::GetGameLevel()
{
	return GameLevel;
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

	if (!startGameOverCount)
	{
		RunTime += DeltaSeconds;
	}
	else
	{
		gameOverTimer += DeltaSeconds;
		if (gameOverTimer >= timeTillGameOver)
		{
			bGameOver = true;
		}
	}
}

bool ABountyDashGameMode::GetGameOver()
{
	return bGameOver;
}

void ABountyDashGameMode::GameOver()
{
	startGameOverCount = true;
}

void ABountyDashGameMode::SetGamePaused(bool gamePaused)
{
	UGameplayStatics::SetGamePaused(this, gamePaused);
}
