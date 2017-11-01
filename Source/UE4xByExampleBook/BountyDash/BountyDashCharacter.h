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
	
	/** Will be called when a coin is picked up by the player.   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ScoreUp();

	/** Handle PowerUp interaction   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void PowerUp(EPowerUp PowerUpType);
	
	// -----------------------------------------------------------------------------------

	// Array of movement locations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	TArray<class ABountyDashTargetPoint*> TargetArray;

	/** will act as the interpolation speed with which the character can swap between lanes.  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	float CharacterSpeed = 10.f;
	
protected:

	// Sets default values for this character's properties
	ABountyDashCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// -----------------------------------------------------------------------------------

	/** Calls to ensure that the character starts the game in th middle most lane  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetCharacterInTheMiddleLane();

	/** Finds a Floor actor, sets KillPoint if succeeded  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetKillPoint();

	/** Finds Target points and sorts them by location  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void FillAndSortTargetArray();
	
	/** Will handle moving the target location of the player left and right  */
	void MoveRight();
	void MoveLeft();
	
	/** Overlap functions to be used upon capsule component collision  */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	/** Overlap functions to be used upon capsule component collision  */
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/**  Stops the character's Smash ability */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void StopSmash() { bCanSmash = false; }

	/**  Stops the character's Magnet ability */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void StopMagnet() { bCanMagnet = false; }
	
	/** Calls to magnet all coins to character in specified area  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CoinMagnet();

	/** Level Restart  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Reset();

	// -----------------------------------------------------------------------------------

	/** Camera Boom for maintaining camera distance to the player  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	/**  Camera we will use as the target view  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	/** Represents the score of the player  */
	UPROPERTY(BlueprintReadOnly)
	int32 Score;

	/** Time to switch on Magnet ability  */
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float SmashTime = 3.f;

	/** Time to switch on Smash ability  */
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetTime = 3.f;

	/** Distance to magnet coins  */
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetReach = 10000.f;

	/** Smash ability flag    */
	bool bCanSmash;

	/** Magnet ability flag  */
	bool bCanMagnet;
	
	/** Kill Point for this Character */
	float KillPoint;

private:
	
	/** Data for character lane positioning - for internal logics and do not need to be engine facing  */
	short CurrentLocation;

	/** Represents character's Desired Location to lerp func in Tick() */
	FVector DesiredLocation;

	/** flag that represents whether character can move forward of not  */
	bool bBeingPushed;

	/**  Audio component for obstacle hit sound */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* HitObstacleSound;

	/** Audio component for coin pickup sound  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* DingSound;

	/** GameMode Reference  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ABountyDashGameMode* BountyDashGameMode;


	/** Calls to handle Movement for each game Tick  */
	void MovementThisTick(float DeltaTime);

public:

	/** Returns the Character's Score  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetScore() const { return Score; }

};
