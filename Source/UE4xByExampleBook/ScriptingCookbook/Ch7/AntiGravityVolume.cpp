// Fill out your copyright notice in the Description page of Project Settings.

#include "AntiGravityVolume.h"
#include "Components/BoxComponent.h"
#include "GravityObject.h"

// Sets default values
AAntiGravityVolume::AAntiGravityVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetBoxExtent(FVector(200.f, 200.f, 400.f));
}

// Called when the game starts or when spawned
void AAntiGravityVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAntiGravityVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAntiGravityVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (IGravityObject* GravityObject = Cast<IGravityObject>(OtherActor))
	{
		GravityObject->EnableGravity();
	}
}

void AAntiGravityVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (IGravityObject* GravityObject = Cast<IGravityObject>(OtherActor))
	{
		GravityObject->DisableGravity();
	}
}

