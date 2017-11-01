// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VSCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AVSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Gun Mesh, will only be seen by self  */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPGunMesh;

	/** First person camera  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCameraComponent;

	/** Projectile Spawn point */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint;

	/** Pawn Noise Emitter Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPawnNoiseEmitterComponent* PawnNoiseEmitterComponent;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* FireAnimation;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USoundBase* FireSound;
	
public:
	
	/** calls to get all necessary data to represent it on HUD Blueprint Widget */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void GetDataForHUD(FText& AmmoText, FText& TargetsText, float& HealthPercent, float& StaminaPercent, FText& CurrentRoundText) const;

	/** calls from dead enemy to increment killed targets */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void AddTargetKilled();

	/**  calls to add AmmoAmount of ammo */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void AddAmmo(int32 AmmoAmount) { CurrentAmmo += AmmoAmount; }

	/** Calls when this character is damaged  */
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:

	// Sets default values for this character's properties
	AVSCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/** Calls in Tick() - updates stamina according character behavior  */
	void HandleStaminaThisFrame(float DeltaTime);

	/**  Calls in Tick() - update zoom if required  */
	void LerpCameraFOV(float DeltaTime);
	
private:
	
	/** Handles forwards and backwards movement  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void MoveForward(float Value);

	/**  Handles left and right strafing movement  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void MoveRight(float Value);

	/** Fires a projectile */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnFire();

	/** calls when SPRINT button is Pressed  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SprintStart() { bWantSprinting = true; }

	/** calls when SPRINT button is Released  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SprintStop() { bWantSprinting = false; }

	/** calls when SPRINT button is Pressed  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ZoomStart() { bShouldZoom = true; }

	/** calls when SPRINT button is Released  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ZoomStop() { bShouldZoom = false; }

	/** calls in BP to create HUD widget and add it to viewport   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CreateHUD();

	/** calls in BP to create Win menu widget and add it to viewport   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CreateWinMenuWidget();

	/** calls in BP to create Win menu widget and add it to viewport   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CreateLoseMenuWidget();

	/** calls to check whether we won or not  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CheckWinCondition();

	/** create win menu  */
	void WinTheGame();

	/** create lose menu  */
	void LoseTheGame();
	


	/** Character's health amount */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 80.f;

	/** Character's MAX available health  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	/** Character's current stamina amount  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float CurrentStamina = 50.f;

	/** Stamina Regen Per Second  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenPerSecond = 1.f;

	/** Stamina Drain Per Second  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float StaminaDrainPerSecond = 10.f;

	/** Character's MAX available stamina   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 100.f;

	/** represent only our intention for sprinting
	*   can we sprint or not will be determined in HandleStaminaThisFrame() function
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bWantSprinting = false;
	
	/** Character's Current Ammo  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo = 30;

	/** Character's Targets kill  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 TargetsKill = 0;

	/** amount of enemies to kill for next level. Will be init in BeginPlay. Needs to show in HUD blueprint */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 TargetsGoal = 999;

	/** game current round. Will be init in BeginPlay.  Needs to show in HUD blueprint */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentRound = 999;
	
	// Projectile class to use
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AVSProjectile> ProjectileClass;

	

	/** shows whether we should zoom or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bShouldZoom = false;

	/** NormalFOV */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float NormalFOV = 90.f;

	/** ZoomFOV */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float ZoomFOV = 20.f;

	/** Zoom Interp Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float InterpSpeed = 5.f;

	/** HUD widget template  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** Win widget template  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> LoseMenuWidgetClass;
	
	/** win menu widget template  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> WinMenuWidgetClass;

	/** current HUD widget reference  */
	UPROPERTY()
	class UUserWidget* CurrentHUDWidget;	
	
	/** current win menu widget reference  */
	UPROPERTY()
	class UUserWidget* WinLoseMenuWidget;

	/** RunningNoiseTimer  */
	FTimerHandle NoiseRunningTimer;

	/** time delay for MakeNoiseWhenRunning() function  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float NoiseRunningTimmerTickInterval = 0.5f;

	/** calls to generate some noise  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void MakeNoiseWhenRunning();
	
public:	
	
	/** Returns current character's health  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetHealth() const { return CurrentHealth; }
	
	/** returns Projectile Spawn Point **/
	FORCEINLINE class USceneComponent* GetProjectileSpawnPoint() const { return ProjectileSpawnPoint; }

};
