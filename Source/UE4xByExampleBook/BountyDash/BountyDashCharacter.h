// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PowerUpObject.h"
#include "BountyDashCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABountyDashCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ABountyDashCharacter();

	void ScoreUp();

	void PowerUp(EPowerUp Type);

	int32 GetScore() const { return Score; }

	
	// Array of movement locations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	TArray<class ATargetPoint*> TargetArray;

	// Character lane swap speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	float CharacterSpeed;
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Will handle moving the target location of the player left and right
	void MoveRight();

	void MoveLeft();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void StopSmash();

	UFUNCTION()
	void StopMagnet();
	
	void CoinMagnet();

	UFUNCTION()
	void Reset();

	// Camera Boom for maintaining camera distance to the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// Camera we will use as the target view
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly)
	int32 Score;

	UPROPERTY(EditAnywhere, Category = PowerUps)
	float SmashTime = 3.f;

	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetTime = 3.f;

	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetReach = 10000.f;

	bool CanSmash = true;

	bool CanMagnet;
	
	float Killpoint;

private:
	
	// Data for character lane positioning
	short CurrentLocation;

	FVector DesiredLocation;

	bool bBeingPushed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* HitObstacleSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* DingSound;
	
};
