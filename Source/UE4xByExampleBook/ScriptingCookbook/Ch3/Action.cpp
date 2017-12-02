// Fill out your copyright notice in the Description page of Project Settings.

#include "Action.h"

void UAction::PostInitProperties()
{
	Super::PostInitProperties();

	// UE_LOG(LogTemp, Error, TEXT("UAction::PostInitProperties()"));
}

void UAction::BeginDestroy()
{
	Super::BeginDestroy();

	// UE_LOG(LogTemp, Error, TEXT("UAction::BeginDestroy()"));
}
