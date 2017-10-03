// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBase.h"

#include "Components/SphereComponent.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(PickupMesh);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(200.f);
}

void APickupBase::OnGetCollected_Implementation(AActor* OtherActor)
{
	// UE_LOG(LogTemp, Error, TEXT(" APickupBase::OnGetCollected_Implementation(). "));
}

