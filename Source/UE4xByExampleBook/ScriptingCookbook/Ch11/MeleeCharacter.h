// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MeleeCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AMeleeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	

protected:

	// Sets default values for this character's properties
	AMeleeCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	

	
	
};
