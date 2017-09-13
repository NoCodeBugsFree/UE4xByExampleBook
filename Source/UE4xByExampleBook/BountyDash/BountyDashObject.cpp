// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashObject.h"
#include "Components/SphereComponent.h"
#include "BountyDashGameMode.h"

// Sets default values
ABountyDashObject::ABountyDashObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	check(Collider);
	SetRootComponent(Collider);
	Collider->SetCollisionProfileName("OverlapAllDynamic");

	OnActorBeginOverlap.AddDynamic(this, &ABountyDashObject::MyOnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &ABountyDashObject::MyOnActorEndOverlap);

}

// Called when the game starts or when spawned
void ABountyDashObject::BeginPlay()
{
	Super::BeginPlay();
	
	BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode());
	check(BountyDashGameMode);
}

// Called every frame
void ABountyDashObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BountyDashGameMode && !IsPendingKill())
	{
		float GameSpeed = BountyDashGameMode->GetInverseGameSpeed();
		AddActorLocalOffset(FVector(GameSpeed, 0.f, 0.f));
		if (GetActorLocation().X < KillPoint)
		{
			Destroy();
		}
	}
}

void ABountyDashObject::MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}

void ABountyDashObject::MyOnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}

