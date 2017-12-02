// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Killable.h"
#include "Undead.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UUndead : public UKillable
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE4XBYEXAMPLEBOOK_API IUndead : public IKillable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual bool IsDead() override;
	virtual void Die() override;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	virtual void Turn();

	UFUNCTION(BlueprintCallable, Category = "AAA")
	virtual void Banish();
	
};
