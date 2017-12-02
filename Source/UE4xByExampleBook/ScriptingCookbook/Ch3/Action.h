// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * 
 */
UCLASS( BlueprintType, Blueprintable )
class UE4XBYEXAMPLEBOOK_API UAction : public UObject
{
	GENERATED_BODY()
	
public:

	/**
	* Called after the C++ constructor and after the properties have been initialized, including those loaded from config.
	* mainly this is to emulate some behavior of when the constructor was called after the properties were initialized.
	*/
	virtual void PostInitProperties() override;

	/**
	* Called before destroying the object.  This is called immediately upon deciding to destroy the object, to allow the object to begin an
	* asynchronous cleanup process.
	*/
	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FKey ShortcutKey;
	
};
