// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Gladiator.generated.h"

UCLASS(config = Game)
class UE4XBYEXAMPLEBOOK_API AGladiator : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	/**  Follow camera  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** The sprite used to draw effect, better and more controllable than using the HUD or Textures  */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	//class UPaperSpriteComponent* EffectSprite;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate.  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate = 45.f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate.  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate = 45.f;

	/** Base Jump velocity  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float JumppingVelocity = 600.f;

	/** Is the player dead or not  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool IsStillAlive = true;

	/** is the player attacking right now?  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool IsAttacking = false;

	/** the index of the current active weapon.  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 WeaponIndex = 1;

	/**  To be able to disable the player during cutscenes, menus, death.... */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool IsControlable = true;

	/** to hold the active instance of the game tables  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UDataTable* TablesInstance;

	/**  Total character's health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float TotalHealth = 100.f;

	/**  Current character's health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 100.f;

	/**  the current weapon attacking range */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 25.f;

public:
	


protected:
	
	// Sets default values for this character's properties
	AGladiator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// -----------------------------------------------------------------------------------

	/** Enable or disable inputs  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnSetPlayerController(bool Status);

	/** the attack effect on health  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnChangeHealthByAmount(float UsedAmount);

	/** A method that holds some procedurals after the player has done an attack.  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnPostAttack();

	/** A method that holds the code responsible for player movement to the forward and backward.  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void MoveForward(float Value);
	
	/** A method that holds the code responsible for player movement to the left and right.  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void MoveRight(float Value);
	
	/** A method that is responsible for applying the jump action to the character based on the base character class.  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Jump();

	/** responsible for stopping the jump, and resuming the idle/run animation.  */
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void StopJumping();

	/** method that is responsible for attacking.  */
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void OnAttack();

	/** method that is responsible for switching between weapons.  */
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void OnChangeWeapon();

	/** method that is responsible for applying turns to the following camera.  */
	void TurnAtRate(float Rate);

	/** method that is responsible for applying the camera look - up rate to the follow camera.  */
	void LookUpAtRate(float Rate);

private:



public:	
	
	/** Return if the player dead or alive  */
	UFUNCTION(BlueprintCallable, Category = "Player Attributes")
	bool GetIsStillAlive() const { return IsStillAlive; }

	/** returns the TotalHealth value  */
	UFUNCTION(BlueprintCallable, Category = "Player Attributes")
	float OnGetHealthAmount() const { return TotalHealth; }

	/**  Returns CameraBoom subobject  */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/**  Returns FollowCamera subobject */
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
};
