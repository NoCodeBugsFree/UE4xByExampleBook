// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Interactable.h"
#include "DoorBell.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ADoorBell : public AStaticMeshActor, public IInteractable
{
	GENERATED_BODY()
	
public:

	ADoorBell();
	
	//~ Begin Interactable Interface
	virtual bool CanInteract_Implementation() override;
	virtual void PerformInteract_Implementation() override;
	//~ End Interactable Interface
	
	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	AActor* DoorToOpen;

	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bHasBeenPushed = false;

};
