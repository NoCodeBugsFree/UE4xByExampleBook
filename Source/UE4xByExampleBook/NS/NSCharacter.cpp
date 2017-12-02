// Fill out your copyright notice in the Description page of Project Settings.

#include "NSCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"
#include "NSPlayerState.h"
#include "NSGameMode.h"
#include "DrawDebugHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ANSCharacter::ANSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	
	// Position the camera
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); 

	/**
	 * If this camera component is placed on a pawn, should it use the view/control rotation of the pawn where possible?
	 * @see APawn::GetViewRotation()
	 */
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FP_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FP_Mesh->SetOnlyOwnerSee(true);				// Set so only owner can see mesh
	FP_Mesh->SetupAttachment(FirstPersonCameraComponent);	// Attach mesh to FirstPersonCameraComponent
	FP_Mesh->bCastDynamicShadow = false;			// Disallow mesh to cast dynamic shadows
	FP_Mesh->CastShadow = false;				// Disallow mesh to cast other shadows

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// Only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;		// Disallow mesh to cast dynamic shadows
	FP_Gun->CastShadow = false;			// Disallow mesh to cast other shadows
	FP_Gun->SetupAttachment(FP_Mesh, TEXT("GripPoint"));

	// Create a TP gun mesh component
	TP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP_Gun"));
	TP_Gun->SetOwnerNoSee(true);
	TP_Gun->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	/** we don't want to see TP mesh  */
	GetMesh()->SetOwnerNoSee(true);

	// Create particles
	TP_GunShotParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSysTP"));
	TP_GunShotParticle->bAutoActivate = false;
	TP_GunShotParticle->SetupAttachment(TP_Gun);
	TP_GunShotParticle->SetOwnerNoSee(true);

	// Create particle
	FP_GunShotParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FP_GunShotParticle"));
	FP_GunShotParticle->bAutoActivate = false;
	FP_GunShotParticle->SetupAttachment(FP_Gun);
	FP_GunShotParticle->SetOnlyOwnerSee(true);

	BulletParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletSysTP"));
	BulletParticle->bAutoActivate = false;
	BulletParticle->SetupAttachment(FirstPersonCameraComponent);
	
	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}

// Called when the game starts or when spawned
void ANSCharacter::BeginPlay()
{
	Super::BeginPlay();

	// [Client]
	if (Role < ROLE_Authority)
	{
		SetTeam(CurrentTeam);
	}
}

// Called every frame
void ANSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ANSCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ANSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANSCharacter::MoveRight);

	// Bind Turn events
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ANSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANSCharacter, CurrentTeam);
}

float ANSCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	/** if we are a server && we are not shooting yourself && we are alive  */
	if (Role == ROLE_Authority && DamageCauser != this && NSPlayerState->GetHealth() > 0)
	{
		/** reduce the health  */
		NSPlayerState->AddHealth(-Damage);

		/** play our pain effects  */
		PlayPain();

		/** if we are going to die  */
		if (NSPlayerState->GetHealth() <= 0)
		{
			/** increase our death counter  */
			NSPlayerState->AddDeaths();

			// Ragdoll our Player 
			MultiCastRagdoll();

			/** Increase our killer's score  */
			if (ANSCharacter* OurKiller = Cast<ANSCharacter>(DamageCauser))
			{
				OurKiller->NSPlayerState->AddScore();
			}
			
			// respawn ourself after 3 sec
			FTimerHandle RespawnTimer;
			GetWorldTimerManager().SetTimer<ANSCharacter>(RespawnTimer, this, &ANSCharacter::Respawn, 3.0f, false);
		}
	}
	return Damage;
}

void ANSCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	/** set the PlayerState reference  */
	NSPlayerState = Cast<ANSPlayerState>(PlayerState);

	/** reinitialize health  */
	if (Role == ROLE_Authority && NSPlayerState)
	{
		NSPlayerState->ReinitializeHealth();
	}
}

void ANSCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ANSCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ANSCharacter::OnFire()
{
	// try and play a FP firing animation if specified
	PlayFirstPersonEffects();

	
	/**  Global engine pointer. Can be 0 so don't use without checking.  */
	if (GEngine)
	{
		FVector MousePosition;
		FVector MouseDirection;
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		FVector2D ScreenPos = GEngine->GameViewport->Viewport->GetSizeXY();

		/** Convert 2D screen position to World Space 3D position and direction. Returns false if unable to determine value. **/
		PlayerController->DeprojectScreenPositionToWorld(ScreenPos.X / 2.0f, ScreenPos.Y / 2.0f, MousePosition, MouseDirection);
		MouseDirection *= 10000000.0f;
		
		ServerFire(MousePosition, MouseDirection);
	}
}

void ANSCharacter::PlayFirstPersonEffects()
{
	if (FP_FireAnimaiton)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = FP_Mesh->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FP_FireAnimaiton, 1.f);
		}
	}

	// Play the FP particle effect if specified
	if (FP_GunShotParticle)
	{
		FP_GunShotParticle->Activate(true);
	}
}

void ANSCharacter::Fire(const FVector Position, const FVector Direction)
{
	// Perform Raycast
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel3); // ECC_GameTraceChannel3 - "Character"
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit, Position, Direction, CollisionObjectQueryParams, CollisionQueryParams);
	DrawDebugLine(GetWorld(), Position, Direction, FColor::Red, true, 100, 0, 5.f);

	/**  bBlockingHit Indicates if this hit was a result of blocking collision. If false, there was no hit or it was an overlap/touch instead. */
	if (Hit.bBlockingHit)
	{	

		ANSCharacter* OtherCharacter = Cast<ANSCharacter>(Hit.GetActor());
		
		if (OtherCharacter && OtherCharacter->GetNSPlayerState() && OtherCharacter->GetNSPlayerState()->GetTeam() != GetNSPlayerState()->GetTeam())
		{
			FDamageEvent DamageEvent(UDamageType::StaticClass());
			OtherCharacter->TakeDamage(WeaponDamage, DamageEvent, GetController(), this);
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			
			/**
			* Play a force feedback pattern on the player's controller
			* @param	ForceFeedbackEffect		The force feedback pattern to play
			* @param	bLooping				Whether the pattern should be played repeatedly or be a single one shot
			* @param	Tag						A tag that allows stopping of an effect.  If another effect with this Tag is playing, it will be stopped and replaced
			*/
			
			if (HitSuccessFeedback)
			{
				
				// PlayerController->ClientPlayForceFeedback(HitSuccessFeedback, false, NAME_None, false, false, FName(TEXT("")));
			}
		}
	}
}

bool ANSCharacter::ServerFire_Validate(const FVector Position, const FVector Direction)
{
	if (Position != FVector(ForceInit) && Direction != FVector(ForceInit))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ANSCharacter::ServerFire_Implementation(const FVector Position, const FVector Direction)
{
	Fire(Position, Direction);

	MultiCastShootEffects();
}

void ANSCharacter::MultiCastShootEffects_Implementation()
{
	// try and play a TP firing animation if specified
	if (TP_FireAnimaiton)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(TP_FireAnimaiton, 1.f);
		}
	}

	// try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (TP_GunShotParticle)
	{
		TP_GunShotParticle->Activate(true);
	}

	if (BulletParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletParticle->Template, BulletParticle->GetComponentLocation(),
			BulletParticle->GetComponentRotation());
	}
}

void ANSCharacter::MultiCastRagdoll_Implementation()
{
	GetMesh()->SetPhysicsBlendWeight(1.0f);

	GetMesh()->SetSimulatePhysics(true);

	GetMesh()->SetCollisionProfileName("Ragdoll");
}

void ANSCharacter::PlayPain_Implementation()
{
	if (Role == ROLE_AutonomousProxy)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PainSound, GetActorLocation());
	}
}

ANSPlayerState* ANSCharacter::GetNSPlayerState()
{
	if (NSPlayerState)
	{
		return NSPlayerState;
	}
	else
	{
		NSPlayerState = Cast<ANSPlayerState>(PlayerState);
		return NSPlayerState;
	}
}

void ANSCharacter::SetNSPlayerState(class ANSPlayerState* NewPlayerState)
{
	// Ensure PS is valid and only set on server
	if (NewPlayerState && Role == ROLE_Authority)
	{
		NSPlayerState = NewPlayerState;
		PlayerState = NewPlayerState;
	}
}

void ANSCharacter::Respawn()
{
	if (Role == ROLE_Authority)
	{	
		/** reinit self health  */
		NSPlayerState->ReinitializeHealth();
		
		/** respawn  */
		if (ANSGameMode* NSGameMode = Cast<ANSGameMode>(GetWorld()->GetAuthGameMode()))
		{
			NSGameMode->Respawn(this);

			/**
			* Destroy this actor. Returns true the actor is destroyed or already marked for destruction, false if indestructible.
			* Destruction is latent. It occurs at the end of the tick.
			* @param	bNetForce				[opt] Ignored unless called during play.  Default is false.
			* @param	bShouldModifyLevel		[opt] If true, Modify() the level before removing the actor.  Default is true.
			* returns	true if destroyed or already marked for destruction, false if indestructible.
			*/
			Destroy(true, true);
		}
	}
}

void ANSCharacter::SetTeam_Implementation(ETeam NewTeam)
{
	FLinearColor CharacterBodyColour;
	if (NewTeam == ETeam::BLUE_TEAM)
	{
		CharacterBodyColour = FLinearColor(0.0f, 0.0f, 0.5f);
	}
	else
	{
		CharacterBodyColour = FLinearColor(0.5f, 0.0f, 0.0f);
	}

	if (DynamicCharacterMaterial == nullptr)
	{
		DynamicCharacterMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
		DynamicCharacterMaterial->SetVectorParameterValue(TEXT("BodyColor"), CharacterBodyColour);

		GetMesh()->SetMaterial(0, DynamicCharacterMaterial);
		FP_Mesh->SetMaterial(0, DynamicCharacterMaterial);
	}
}
