// Fill out your copyright notice in the Description page of Project Settings.

#include "OutController.h"
#include "Ch8FunctionLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

AOutController::AOutController()
{
	AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AI Perception Stimuli Source Component"));
	
	/** laser is disabled by default  */
	bIsLaserEnable = false;

}

void AOutController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/** enable laser if needed  */
	if (bIsLaserEnable)
	{
		UCh8FunctionLibrary::LaserFromController(this);
	}
}

void AOutController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Laser", IE_Pressed, this, &AOutController::LaserEnabled);
	InputComponent->BindAction("Laser", IE_Released, this, &AOutController::LaserDisabled);
}

void AOutController::LaserEnabled()
{
	bIsLaserEnable = true;
}

void AOutController::LaserDisabled()
{
	bIsLaserEnable = false;
}
