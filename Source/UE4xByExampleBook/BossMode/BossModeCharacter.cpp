// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "BossModeProjectile.h"
#include "Engine.h"
#include "BossCharacter.h"

// Sets default values
ABossModeCharacter::ABossModeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Set the character turn rates
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Create a CameraComponent
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());

	// Position the camera
	FPCameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	FPCameraComponent->bUsePawnControlRotation = true;

	/** Hands  */
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->SetupAttachment(FPCameraComponent);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;

	/** Gun  */
	FPGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FPGunMesh->SetOnlyOwnerSee(true);// only the owning player will see mesh
	FPGunMesh->bCastDynamicShadow = false;
	FPGunMesh->CastShadow = false;
	FPGunMesh->SetupAttachment(FPMesh, TEXT("GripPoint"));

	/** Projectile Spawn Point  */
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(FPGunMesh);
}

// Called when the game starts or when spawned
void ABossModeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossModeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossModeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABossModeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABossModeCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABossModeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABossModeCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABossModeCharacter::OnFire);

	PlayerInputComponent->BindAction("Track", IE_Pressed, this, &ABossModeCharacter::OnTrack);
}

void ABossModeCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ABossModeCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ABossModeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABossModeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABossModeCharacter::OnFire()
{
	// Attempt to fire Projectile
	if (ProjectileClass && GetWorld() && ProjectileSpawnPoint)
	{
		ABossModeProjectile* BossModeProjectile = GetWorld()->SpawnActor<ABossModeProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
		if (BossModeProjectile)
		{
			BossModeProjectile->GetProjectileMovement()->HomingTargetComponent = TrackingSceneComponent;
		}
	}
}

void ABossModeCharacter::OnTrack()
{
	FVector MousePosition;
	FVector MouseDirection;
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (GEngine && GEngine->GameViewport && PlayerController)
	{
		FVector2D ScreenPos = GEngine->GameViewport->Viewport->GetSizeXY();
		PlayerController->DeprojectScreenPositionToWorld(ScreenPos.X / 2.0f, ScreenPos.Y / 2.0f, MousePosition, MouseDirection);
		MouseDirection *= 100000.0f;
		GetWorld()->LineTraceSingleByObjectType(Hit, MousePosition, MouseDirection, ObjectQueryParams);

		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRACE HIT WITH %s"), *(Hit.GetActor()->GetName()));
			
			/** sets the TrackingSceneComponent to required Boss SceneComponent [Book Way]  */
			// TrackingSceneComponent = Cast<USceneComponent>(Hit.GetActor()->GetComponentByClass(USceneComponent::StaticClass()));

			/** if we hit a boss  */
			if (ABossCharacter* BossCharacter = Cast<ABossCharacter>(Hit.GetActor()))
			{
				/** and he have valid Projectile Scene Component  */
				if (USceneComponent* ProjectileSceneComponent = BossCharacter->GetProjectileSceneComponent())
				{
					/** sets the TrackingSceneComponent to specified Projectile Scene Component */
					TrackingSceneComponent = ProjectileSceneComponent;
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Trace"));
			TrackingSceneComponent = nullptr;
		}
	}
}