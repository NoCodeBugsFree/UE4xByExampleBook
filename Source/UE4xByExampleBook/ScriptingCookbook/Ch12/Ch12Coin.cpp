// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch12Coin.h"


// Sets default values
ACh12Coin::ACh12Coin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SetRootComponent(Body);

	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->SetupAttachment(Body);

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(Turret);

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	Barrel->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ACh12Coin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACh12Coin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target)
	{
		FVector DirectioinToTarget = Target->GetActorLocation() - GetActorLocation();

		FVector DirectioinFromTarget = GetActorLocation() - Target->GetActorLocation();
		
		FMatrix RotationMatrix = FRotationMatrix::MakeFromX(DirectioinToTarget); // or DirectioinFromTarget
		
		FRotator DesiredRotation = RotationMatrix.Rotator();

		/** simple - without max degrees per second  */
		Turret->SetWorldRotation(FRotator(0.f, DesiredRotation.Yaw, 0.f));
		SceneComponent->SetRelativeRotation(FRotator(FMath::Clamp(DesiredRotation.Pitch, MinElevation, MaxElevation), 0.f, 0.f));
	}
}

