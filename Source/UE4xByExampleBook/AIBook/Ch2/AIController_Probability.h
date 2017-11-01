// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Probability.generated.h"


UENUM(BlueprintType)
enum class EState : uint8
{
	S_Wander UMETA(DisplayName = "Wander"),
	S_Flee UMETA(DisplayName = "Flee"),
	S_Attack UMETA(DisplayName = "Attack"),
};

/**
*
*/

UCLASS()
class UE4XBYEXAMPLEBOOK_API AAIController_Probability : public AAIController
{
	GENERATED_BODY()
	
public:

	void SetEnemyState(EState NewState) { State = NewState; }

protected:

	void Possess(APawn* Pawn) override;

	/** calls every second to move AI to random point  */
	void MoveToNextRandomPoint();

private:
	
	/** Enemy current state  */
	EState State = EState::S_Wander;
};
