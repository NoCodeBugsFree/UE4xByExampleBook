 // Fill out your copyright notice in the Description page of Project Settings.

#include "PostBeginPlay.h"


// Add default functionality here for any IPostBeginPlay functions that are not pure virtual.

void IPostBeginPlay::OnPostBeginPlay()
{
	UE_LOG(LogTemp, Error, TEXT("PostBeginPlay called"));
}
