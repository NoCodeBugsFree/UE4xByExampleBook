// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PhysicsBallGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API APhysicsBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float GlobalAlignment = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float GlobalCohesion = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float GlobalSeparation = 0.2f;

public:

	FORCEINLINE float GetGlobalAlignment() const { return GlobalAlignment; }

	FORCEINLINE float GetGlobalCohesion() const { return GlobalCohesion; }

	FORCEINLINE float GetGlobalSeparation() const { return GlobalSeparation; }
	
};
