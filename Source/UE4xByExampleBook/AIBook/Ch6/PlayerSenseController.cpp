// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSenseController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

APlayerSenseController::APlayerSenseController()
{
	AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));
}
