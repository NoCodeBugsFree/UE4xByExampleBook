// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OutController.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AOutController : public APlayerController
{
	GENERATED_BODY()

	/** AI Perception Stimuli Source Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource;
	
protected:

	AOutController();

	void Tick(float DeltaSeconds) override;

	/** Allows the PlayerController to set up custom input bindings. */
	void SetupInputComponent() override;

	/** calls to enable "Laser"  */
	void LaserEnabled();

	/** calls to disable "Laser"  */
	void LaserDisabled();
	
private:

	/** shows whether laser is enable now or not  */
	uint32 bIsLaserEnable : 1;
	
};
