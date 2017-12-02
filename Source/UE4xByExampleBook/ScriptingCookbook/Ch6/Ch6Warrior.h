// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ch6Warrior.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ACh6Warrior : public ACharacter
{
	GENERATED_BODY()

public:
	

protected:

	// Sets default values for this character's properties
	ACh6Warrior();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:


	FVector2D LastInput;
	
	void Forward(float Amount);
	void Back(float Amount);
	void Left(float Amount);
	void Right(float Amount);

public:	
	

	
};
