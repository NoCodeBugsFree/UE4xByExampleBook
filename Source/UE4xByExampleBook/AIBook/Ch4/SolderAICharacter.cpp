// Fill out your copyright notice in the Description page of Project Settings.

#include "SolderAICharacter.h"


// Sets default values
ASolderAICharacter::ASolderAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASolderAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASolderAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASolderAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

