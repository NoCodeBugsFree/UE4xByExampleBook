// Fill out your copyright notice in the Description page of Project Settings.

#include "Selectable.h"


// Add default functionality here for any ISelectable functions that are not pure virtual.

bool ISelectable::IsCubeSelectable()
{
	UE_LOG(LogTemp, Error, TEXT("IsSelectable"));
	return true;
}

bool ISelectable::TrySelect()
{
	UE_LOG(LogTemp, Error, TEXT("Accepting Selection"));
	return true;
}

void ISelectable::Deselect()
{
	unimplemented();
}
