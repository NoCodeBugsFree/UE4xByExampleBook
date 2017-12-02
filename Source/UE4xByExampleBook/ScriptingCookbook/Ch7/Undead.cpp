// Fill out your copyright notice in the Description page of Project Settings.

#include "Undead.h"


// Add default functionality here for any IUndead functions that are not pure virtual.

bool IUndead::IsDead()
{
	return true;
}

void IUndead::Die()
{
	UE_LOG(LogTemp, Error, TEXT("You can't kill what is already dead. Mwahaha"));
}

void IUndead::Turn()
{
	UE_LOG(LogTemp, Error, TEXT("I'm fleeing!"));
}

void IUndead::Banish()
{
	AActor* Me = Cast<AActor>(this);
	if (Me && !Me->IsPendingKill())
	{
		UE_LOG(LogTemp, Error, TEXT("%s was banished"), *Me->GetName());
		Me->Destroy();
	}
}
