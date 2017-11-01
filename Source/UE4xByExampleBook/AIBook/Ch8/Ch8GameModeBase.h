// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ch8GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ACh8GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	void SpawnDebugActorAtLocation(FVector Location);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	TSubclassOf<class ADebugActor> DebugActorType;
};
