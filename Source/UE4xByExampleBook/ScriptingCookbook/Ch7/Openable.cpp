// Fill out your copyright notice in the Description page of Project Settings.

#include "Openable.h"


// Add default functionality here for any IOpenable functions that are not pure virtual.

void IOpenable::Open_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Please override me! =)"));
}
