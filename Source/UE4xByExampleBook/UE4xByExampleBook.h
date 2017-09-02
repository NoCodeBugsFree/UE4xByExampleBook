// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/** This is a good place to
  * include utility functions you wish all objects to have access to. 
  */

template<typename T>
T* GetCustomGameMode(UWorld* WorldContext)
{
	return Cast<T>(WorldContext->GetAuthGameMode());
}