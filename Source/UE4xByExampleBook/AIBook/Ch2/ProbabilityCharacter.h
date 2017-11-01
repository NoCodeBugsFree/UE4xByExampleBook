// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProbabilityCharacter.generated.h"


UCLASS()
class UE4XBYEXAMPLEBOOK_API AProbabilityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	

protected:

	// Sets default values for this character's properties
	AProbabilityCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	/** Pawn Sensing Component  */
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComponent;
	
	/** Calls every time when this character see the player  */
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);
};
