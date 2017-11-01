// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerSenseController.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API APlayerSenseController : public APlayerController
{
	GENERATED_BODY()
	
	/** AI Perception Stimuli Source Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource;
	
protected:

	APlayerSenseController();

};
