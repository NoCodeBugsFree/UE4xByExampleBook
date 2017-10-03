// Fill out your copyright notice in the Description page of Project Settings.

#include "BellzGameMode.h"
#include "ConstructorHelpers.h"

ABellzGameMode::ABellzGameMode()
{
	/** sets player character BP  */
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MasteringUE4x/BP/BP_Gladiator"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}