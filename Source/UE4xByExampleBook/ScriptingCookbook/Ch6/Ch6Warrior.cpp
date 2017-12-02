// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch6Warrior.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
ACh6Warrior::ACh6Warrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACh6Warrior::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACh6Warrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller)
	{
		float Len = LastInput.Size();
		if (Len > 1.f)
		{
			LastInput /= Len;
		}

		AddMovementInput(GetActorForwardVector(), LastInput.Y);
		AddMovementInput(GetActorRightVector(), LastInput.X);

		// Zero off last input values
		LastInput = FVector2D(0.f, 0.f);
	}
}

// Called to bind functionality to input
void ACh6Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// movement
	PlayerInputComponent->BindAxis("Forward", this, &ACh6Warrior::Forward);
	PlayerInputComponent->BindAxis("Back", this, &ACh6Warrior::Back);
	PlayerInputComponent->BindAxis("Left", this, &ACh6Warrior::Left);
	PlayerInputComponent->BindAxis("Right", this, &ACh6Warrior::Right);

	/** mouse  */
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	// jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void ACh6Warrior::Forward(float Amount)
{
	LastInput.Y += Amount;
}

void ACh6Warrior::Back(float Amount)
{
	LastInput.Y += -Amount;
}

void ACh6Warrior::Left(float Amount)
{
	LastInput.X += -Amount;
}

void ACh6Warrior::Right(float Amount)
{
	LastInput.X += +Amount;
}

