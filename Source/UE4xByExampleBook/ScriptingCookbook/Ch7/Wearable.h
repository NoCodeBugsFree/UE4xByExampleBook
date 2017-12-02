// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wearable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWearable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE4XBYEXAMPLEBOOK_API IWearable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Wearable)
	int32 GetStrengthRequirement();
	virtual int32 GetStrengthRequirement_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Wearable)
	bool CanEquip(APawn* Wearer);
	virtual bool CanEquip_Implementation(APawn* Wearer);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Wearable)
	void OnEquip(APawn* Wearer);
	virtual void OnEquip_Implementation(APawn* Wearer);
	
};
