// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossModeCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABossModeCharacter : public ACharacter
{
	GENERATED_BODY()

	// Pawn Mesh, will only be seen by self
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPMesh;

	// Gun Mesh, will only be seen by self
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPGunMesh;

	// First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCameraComponent;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate = 45.0f;
	
	// Base Lookup/Down rate in deg/sec
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate = 45.0f;

	// Projectile class to use
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABossModeProjectile> ProjectileClass;
	
protected:

	// Sets default values for this character's properties
	ABossModeCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles forwards and backwards movement
	void MoveForward(float Val);

	// Handles left and right strafing movement
	void MoveRight(float Val);

	/**
	* Will be called via input axis mapping
	* @param Rate this is the normalized rate, 1.0 means full turn rate
	*/
	void TurnAtRate(float Rate);
	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate this is the normalized rate, 1.0 means full turn rate
	*/
	void LookUpAtRate(float Rate);
	
	/** Fires a projectile and sets TrackingSceneComponent */
	void OnFire();

	/** Attempt to setup TrackingSceneComponent to valid value if we successfully LineTraceSingleByObjectType the Boss character */
	void OnTrack();


	/** Projectile Spawn  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
	class USceneComponent* ProjectileSpawnPoint;
	
	/** HomingTargetComponent - attract point for this projectile  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* TrackingSceneComponent;
	
};
