// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Talker.h"
#include "TalkingMesh.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ATalkingMesh : public AStaticMeshActor, public ITalker
{
	GENERATED_BODY()
	
	
public:
	
	//~ Begin ITalker Interface
	virtual void StartTalking_Implementation() override;
	virtual void StartCrying_Implementation(FVector Vector, int32 Value) override;
	//~ End ITalker Interface

protected:

	ATalkingMesh();

private:
	
};
