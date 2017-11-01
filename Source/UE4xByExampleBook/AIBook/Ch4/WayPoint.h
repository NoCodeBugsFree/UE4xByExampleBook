// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "WayPoint.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AWayPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:

	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	TArray<class ASolderAICharacter*> AllowedAccess;
	
	
};
