// Fill out your copyright notice in the Description page of Project Settings.

#include "VSCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "VSProjectile.h"
#include "Blueprint/UserWidget.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "VSGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AVSCharacter::AVSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());

	/** FPMesh  */
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(FPCameraComponent);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;

	/** Gun  */
	FPGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FPGunMesh->SetOnlyOwnerSee(true);// only the owning player will see mesh
	FPGunMesh->bCastDynamicShadow = false;
	FPGunMesh->CastShadow = false;
	FPGunMesh->SetupAttachment(GetMesh(), TEXT("GripPoint"));

	/** Projectile Spawn Point  */
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(FPGunMesh);

	/** Pawn Noise Emitter Component  */
	PawnNoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComponent"));

	/** allow mouse up/down  */
	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void AVSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CreateHUD();
	
	/** init TargetsGoal variable and CurrentRound from GameMode   */
	if (AVSGameMode* VSGameMode = Cast<AVSGameMode>(GetWorld()->GetAuthGameMode()))
	{
		TargetsGoal = VSGameMode->GetTargetGoal();
		CurrentRound = VSGameMode->GetCurrentRound();
	}
}

// Called every frame
void AVSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/** Lerp zoom this tick  */
	LerpCameraFOV(DeltaTime);

	/** Set walk speed according to our desire and capability  */
	HandleStaminaThisFrame(DeltaTime);
}

void AVSCharacter::HandleStaminaThisFrame(float DeltaTime)
{
	// ------------------  stamina drain   --------------------------------------------

	/** if we is sprinting and have some stamina to drain  */
	
	bool bShouldDrainStamina = CurrentStamina > 0;
	float Speed = GetCharacterMovement()->Velocity.Size();
	
	/** if sprint key is pressed  */
	if (bWantSprinting)
	{
		if (Speed == 0.f)
		{
			/** replenish stamina this frame */
			CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenPerSecond * DeltaTime, 0.f, MaxStamina);
		}
		else if (Speed > 0.f && Speed < 600.f && bShouldDrainStamina)
		{
			/** run !  */
			GetCharacterMovement()->MaxWalkSpeed = 2200.f;
		} 
		else if (Speed > 600.f && bShouldDrainStamina)
		{
			/** drain stamina  */
			CurrentStamina = FMath::Clamp(CurrentStamina - StaminaDrainPerSecond * DeltaTime, 0.f, MaxStamina);
		}
		else
		{
			/** walk !  */
			GetCharacterMovement()->MaxWalkSpeed = 600.f;
		}
	} 
	else /** if sprint key is released   */
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;

		/** replenish stamina this frame */
		CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenPerSecond * DeltaTime, 0.f, MaxStamina);
	}


	// ---------------  noise generation  ---------------------------------------------

	bool bIsRunning = GetCharacterMovement()->Velocity.Size() > 601.f;
	bool bIsInAir = GetCharacterMovement()->IsFalling();

	/** if we are in air */
	if (bIsInAir)
	{
		/** stop noising  */
		GetWorldTimerManager().ClearTimer(NoiseRunningTimer);
	}
	else /** if we are on the ground  */
	{
		/** start noising  */
		if (bIsRunning)
		{
			/** if NoiseRunningTimer is not ticking - start making noise by timer  */
			if (!NoiseRunningTimer.IsValid())
			{
				GetWorldTimerManager().SetTimer(NoiseRunningTimer, this, &AVSCharacter::MakeNoiseWhenRunning, NoiseRunningTimmerTickInterval, true, 0.f);
			}
		}
		else
		{
			/** stop noising  */
			if (NoiseRunningTimer.IsValid())
			{
				GetWorldTimerManager().ClearTimer(NoiseRunningTimer);
			}
		}
	}
}

void AVSCharacter::LerpCameraFOV(float DeltaTime)
{
	/** if ZOOM button is pressed and we aren't at specified Zoom Field Of View  */
	if (bShouldZoom && !FMath::IsNearlyEqual(FPCameraComponent->FieldOfView, ZoomFOV, 0.01f))
	{
		/** calculate delta zoom this frame  */
		float CurrentFOV = FMath::FInterpTo(FPCameraComponent->FieldOfView, ZoomFOV, DeltaTime, InterpSpeed);

		/** set calculated FOV to our camera */
		FPCameraComponent->SetFieldOfView(CurrentFOV);
	}
	/** if ZOOM button is released and  we aren't at specified Normal Field Of View  */
	else if (!bShouldZoom && !FMath::IsNearlyEqual(FPCameraComponent->FieldOfView, NormalFOV, 0.01f))
	{
		/** calculate delta zoom this frame  */
		float CurrentFOV = FMath::FInterpTo(FPCameraComponent->FieldOfView, NormalFOV, DeltaTime, InterpSpeed);

		/** set calculated FOV to our camera */
		FPCameraComponent->SetFieldOfView(CurrentFOV);
	}
}

// Called to bind functionality to input
void AVSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/**  Jump */
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/**  Sprint */
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AVSCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AVSCharacter::SprintStop);

	/**  Zoom */
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AVSCharacter::ZoomStart);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AVSCharacter::ZoomStop);

	/** Movement */
	PlayerInputComponent->BindAxis("MoveForward", this, &AVSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVSCharacter::MoveRight);

	/**  Turn and LookUp */
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	/** Fire  */
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AVSCharacter::OnFire);
}

float AVSCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= Damage;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	if (CurrentHealth <= 0)
	{
		LoseTheGame();
	}

	return Damage;
}

void AVSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AVSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AVSCharacter::OnFire()
{	
	if (CurrentAmmo > 0)
	{	
		// Attempt to spawn projectile
		if (ProjectileClass && GetWorld() && ProjectileSpawnPoint)
		{
			/** set ownership to further use  */
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			AVSProjectile* VSProjectile = GetWorld()->SpawnActor<AVSProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform(), SpawnParams);
			if (VSProjectile)
			{
				/** play fire animation  */
				if (FireAnimation)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
					if (AnimInstance != NULL)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
				}

				// try and play the sound if specified
				if (FireSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}

				/** reduce ammo */
				CurrentAmmo--;

				/** make noise to notify AI about this fire shot */
				if (PawnNoiseEmitterComponent)
				{
					PawnNoiseEmitterComponent->MakeNoise(this, 1.f, GetActorLocation());
				}
			}
		}
	}
}

void AVSCharacter::CreateHUD()
{
	if (HUDWidgetClass)
	{
		CurrentHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentHUDWidget)
		{
			CurrentHUDWidget->AddToViewport();
		}
	}
}

void AVSCharacter::CreateWinMenuWidget()
{
	if (WinMenuWidgetClass)
	{
		WinLoseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), WinMenuWidgetClass);
		if (WinLoseMenuWidget)
		{
			WinLoseMenuWidget->AddToViewport();
		}
	}
}

void AVSCharacter::CreateLoseMenuWidget()
{
	if (LoseMenuWidgetClass)
	{
		WinLoseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), LoseMenuWidgetClass);
		if (WinLoseMenuWidget)
		{
			WinLoseMenuWidget->AddToViewport();
		}
	}
}

void AVSCharacter::CheckWinCondition()
{
	if (TargetsKill >= TargetsGoal)
	{
		/** create win menu after 1 sec  */
		FTimerHandle WinGameTimer;
		GetWorldTimerManager().SetTimer(WinGameTimer, this, &AVSCharacter::WinTheGame, 1.f, true);
	}
}

void AVSCharacter::WinTheGame()
{
	/** next level must be save in save game object */
	if (AVSGameMode* VSGameMode = Cast<AVSGameMode>(GetWorld()->GetAuthGameMode()))
	{
		VSGameMode->UpdateSaveGameObject();
	}

	/** get player controller  */
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		/** set game paused  */
		PlayerController->SetPause(true);
		
		/** show mouse cursor  */
		PlayerController->bShowMouseCursor = true;

		/** UI Only */
		FInputModeUIOnly InputModeUIOnly;
		PlayerController->SetInputMode(InputModeUIOnly);

		/** Win menu  */
		CreateWinMenuWidget();
	}
}

void AVSCharacter::LoseTheGame()
{
	/** get player controller  */
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		/** set game paused  */
		PlayerController->SetPause(true);

		/** show mouse cursor  */
		PlayerController->bShowMouseCursor = true;

		/** UI Only */
		FInputModeUIOnly InputModeUIOnly;
		PlayerController->SetInputMode(InputModeUIOnly);

		/** Win menu  */
		CreateLoseMenuWidget();
	}
}

void AVSCharacter::MakeNoiseWhenRunning()
{
	/** make noise if we run */
	PawnNoiseEmitterComponent->MakeNoise(this, 0.1f, GetActorLocation());
}

void AVSCharacter::GetDataForHUD(FText& AmmoText, FText& TargetsText, float& HealthPercent, float& StaminaPercent, FText& CurrentRoundText) const
{
	/**  Ammo  */
	FString String = FString::Printf(TEXT("Ammo : %d"), CurrentAmmo);
	AmmoText = FText::FromString(String);

	/** Targets  */
	String = FString::Printf(TEXT("Targets eliminated : %d / %d"), TargetsKill, TargetsGoal);
	TargetsText = FText::FromString(String);

	/** Round  */
	String = FString::Printf(TEXT("Round : %d"), CurrentRound);
	CurrentRoundText = FText::FromString(String);

	/** Health Bar Percentage  */
	HealthPercent = CurrentHealth / MaxHealth;

	/** Stamina Bar Percentage  */
	StaminaPercent = CurrentStamina / MaxStamina;
}

void AVSCharacter::AddTargetKilled()
{
	/** add one target  */
	TargetsKill++;

	/** does we win ?  */
	CheckWinCondition();
}
