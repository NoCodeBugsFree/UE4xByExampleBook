// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE4XBYEXAMPLEBOOK_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interactable)
	bool CanInteract();
	virtual bool CanInteract_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interactable)
	void PerformInteract();
	virtual void PerformInteract_Implementation();
	
};
