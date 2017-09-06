// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeGameMode.h"
#include "ConstructorHelpers.h"

ABossModeGameMode::ABossModeGameMode()
{
	// set default pawn class to our Blueprinted character
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BossMode/BP/BP_BossModeCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
}
