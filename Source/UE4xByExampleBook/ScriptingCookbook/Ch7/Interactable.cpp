// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"


// Add default functionality here for any IInteractable functions that are not pure virtual.

bool IInteractable::CanInteract_Implementation()
{
	return true;
}

void IInteractable::PerformInteract_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Please override me! =)"));
}
