// Fill out your copyright notice in the Description page of Project Settings.

#include "NonSelectableCube.h"




bool ANonSelectableCube::IsCubeSelectable()
{
	UE_LOG(LogTemp, Error, TEXT("NOT Selectable"));
	return true;
}

bool ANonSelectableCube::TrySelect()
{
	UE_LOG(LogTemp, Error, TEXT("Refusing Selection"));
	return true;
}

void ANonSelectableCube::Deselect()
{
	unimplemented();
}
