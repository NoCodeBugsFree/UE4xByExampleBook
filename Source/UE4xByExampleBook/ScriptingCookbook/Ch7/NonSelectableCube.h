// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScriptingCookbook/Ch7/SelectableCube.h"
#include "NonSelectableCube.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ANonSelectableCube : public ASelectableCube
{
	GENERATED_BODY()
	
public:

	virtual bool IsCubeSelectable() override;
	virtual bool TrySelect() override;
	virtual void Deselect() override;
	
	
};
