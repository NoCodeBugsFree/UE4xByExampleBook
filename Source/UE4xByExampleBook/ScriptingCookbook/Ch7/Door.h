// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Interactable.h"
#include "Openable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ADoor : public AStaticMeshActor, public IOpenable, public IInteractable
{
	GENERATED_BODY()
	
public:

	ADoor();

	//~ Begin Interactable Interface
	virtual bool CanInteract_Implementation() override;
	virtual void PerformInteract_Implementation() override;
	//~ End Interactable Interface

	//~ Begin Openable Interface
	virtual void Open_Implementation() override;
	//~ End Openable Interface
	
	
};
