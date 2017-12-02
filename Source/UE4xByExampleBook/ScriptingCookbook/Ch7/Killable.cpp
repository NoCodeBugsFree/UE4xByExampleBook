// Fill out your copyright notice in the Description page of Project Settings.

#include "Killable.h"


// Add default functionality here for any IKillable functions that are not pure virtual.

bool IKillable::IsDead()
{
	return false;
}

void IKillable::Die()
{
	UE_LOG(LogTemp, Error, TEXT("Arrrgh"));
	AActor* Me = Cast<AActor>(this);
	if (Me && !Me->IsPendingKill())
	{
		UE_LOG(LogTemp, Error, TEXT("%s was killed"), *Me->GetName());
		Me->Destroy();
	}
}
