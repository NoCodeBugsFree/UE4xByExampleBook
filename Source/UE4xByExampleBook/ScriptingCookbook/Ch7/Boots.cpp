// Fill out your copyright notice in the Description page of Project Settings.

#include "Boots.h"


int32 ABoots::GetStrengthRequirement_Implementation()
{
	return IWearable::GetStrengthRequirement_Implementation();
}

bool ABoots::CanEquip_Implementation(APawn* Wearer)
{
	return IWearable::CanEquip_Implementation(Wearer);
}

void ABoots::OnEquip_Implementation(APawn* Wearer)
{
	IWearable::OnEquip_Implementation(Wearer);
}

// Sets default values
ABoots::ABoots()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoots::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

