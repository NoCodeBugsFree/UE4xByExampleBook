// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinPickup.h"
#include "Gladiator.h"

void ACoinPickup::OnGetCollected_Implementation(AActor* OtherActor)
{
	/** Use the base pickup behavior  */
	Super::OnGetCollected_Implementation(OtherActor);

	if (AGladiator* Gladiator = Cast<AGladiator>(OtherActor))
	{
		Gladiator->AddCoins(CoinValue);
		SetActive(false);
	}
	
	/** Destroy the coin*/
	Destroy();
}
