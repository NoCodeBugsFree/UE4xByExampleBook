// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsBall.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "PhysicsBallGameModeBase.h"

// Sets default values
APhysicsBall::APhysicsBall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** create ball mesh  */
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball static mesh"));
	SetRootComponent(BallMesh);

	/** setup the ball mesh  */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TestBallMesh(TEXT("/Game/Rolling/Meshes/BallMesh"));
	if (TestBallMesh.Succeeded())
	{
		BallMesh->SetStaticMesh(TestBallMesh.Object);
	}

	/** enable physics  */
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetLinearDamping(0.1f);
	BallMesh->SetAngularDamping(0.1f);
	
	BallMesh->bGenerateOverlapEvents = true;
	BallMesh->SetNotifyRigidBodyCollision(true);

	/** create spring arm  */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 2500.f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bAbsoluteRotation = true;
	SpringArmComponent->SetWorldRotation(FRotator(-65.f, 0.f, 0.f));
	
	/** create camera  */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	/** create sphere component  */
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(300.f);
	
}

void APhysicsBall::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/** create HUD widget  */
	CreateHUD(NewController);
}

// Called when the game starts or when spawned
void APhysicsBall::BeginPlay()
{
	Super::BeginPlay();
	
	/** save the initial location of the pawn  */
	StartLocation = GetActorLocation();

	/** set direction to random unit vector. Z axis ignored   */
	FVector RandomUnitVector = FMath::VRand(); /** Return a uniformly distributed random unit length vector = point on the unit sphere surface. */
	Direction = FVector(RandomUnitVector.X, RandomUnitVector.Y, 0.f);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APhysicsBall::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &APhysicsBall::OnOverlapEnd);

	/** set the Game Mode reference  */
	PhysicsBallGameMode = Cast<APhysicsBallGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void APhysicsBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClearValues();

	RotateSpringArmAccordingMovement(DeltaTime);

	CalculateDirection();

	ApplyTorqueToBall();

	Bounce();

	ForEachOverlapped();

	SetupFlockingBehavior();

	SetLeaderDirection();
}

void APhysicsBall::SetLeaderDirection()
{
	if (Leader)
	{
		FVector SaveNormal = (Leader->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FRotator RotatorFromX = FRotationMatrix::MakeFromY(SaveNormal).Rotator();
		FVector UpVector = FRotationMatrix(RotatorFromX).GetScaledAxis(EAxis::Z);
		LeaderDirection = UpVector;
	}
	else
	{
		LeaderDirection = FVector::ZeroVector;
	}
}

void APhysicsBall::SetupFlockingBehavior()
{
	if (OverlappedPhysicsBalls.Num() > 0 && PhysicsBallGameMode)
	{
		/**  NAlignment */
		FVector AlignmentDividedByNum = NAlignment / OverlappedPhysicsBalls.Num();
		float GlobalAlignment = PhysicsBallGameMode->GetGlobalAlignment();
		AlignmentDividedByNum.Normalize();
		NAlignment = FVector(AlignmentDividedByNum * GlobalAlignment);

		/**  NCohesion */
		FVector CohesionDividedByNum = NCohesion / OverlappedPhysicsBalls.Num();
		float GlobalCohesion = PhysicsBallGameMode->GetGlobalCohesion();
		FVector Minus = CohesionDividedByNum - GetActorLocation();
		Minus.Normalize();
		NCohesion = FVector(Minus * GlobalCohesion);

		/**  NSeperation */
		FVector SeperationDividedByNum = NSeperation / OverlappedPhysicsBalls.Num();
		SeperationDividedByNum *= -1.f;
		float GlobalSeperation = PhysicsBallGameMode->GetGlobalSeparation();
		NSeperation = FVector(SeperationDividedByNum * GlobalSeperation);
	}
}

void APhysicsBall::ClearValues()
{
	NCohesion   = FVector::ZeroVector;
	NAlignment  = FVector::ZeroVector;
	NSeperation = FVector::ZeroVector;
}

void APhysicsBall::RotateSpringArmAccordingMovement(float DeltaTime)
{
	FRotator RotationThisFrame;

	FRotator RotationFromX = FRotationMatrix::MakeFromX(Direction).Rotator();
	FRotator DeltaRotator = FRotator(45.f, 90.f, 0.f);

	FRotator CurrentRotation = SpringArmComponent->GetComponentRotation();
	FRotator TargetRotation = RotationFromX - DeltaRotator;
	TargetRotation.Normalize();

	RotationThisFrame = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 1.f);
	SpringArmComponent->SetRelativeRotation(RotationThisFrame);
}

void APhysicsBall::CalculateDirection()
{
	FVector BP_ZeroVector = FVector::ZeroVector;
	FVector VectorToNormalize = Direction + BP_ZeroVector;
	VectorToNormalize.Normalize();
	Direction = FVector(VectorToNormalize.X, VectorToNormalize.Y, 0.f);
}

void APhysicsBall::ApplyTorqueToBall()
{
	FVector Torque = Direction * FVector(RollTorque, RollTorque, 0.f);
	BallMesh->AddTorque(Torque, NAME_None, true);
}

void APhysicsBall::Bounce()
{
	/** start trace  */
	FVector Start = GetActorLocation();

	FRotator RotatorFromY = FRotationMatrix::MakeFromY(Direction).Rotator();
	FVector TraceDirection = FRotationMatrix(RotatorFromY).GetScaledAxis(EAxis::Z);

	FVector Min, Max;
	BallMesh->GetLocalBounds(Min, Max);

	float Distance = Max.X * (-3.5f);

	/** end trace  */
	FVector End = Start + (TraceDirection * Distance);
	
	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	bool bHasHitSomething = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionQueryParams);
	
	/** if we hit something - change direction  */
	if (bHasHitSomething)
	{
		FRotator RotatorFromY = FRotationMatrix::MakeFromY(OutHit.Normal).Rotator();
		FVector UpVector = FRotationMatrix(RotatorFromY).GetScaledAxis(EAxis::Z);

		Direction = FMath::GetReflectionVector(Direction, UpVector);
	}
}

void APhysicsBall::ForEachOverlapped()
{
	for (AActor* TestBall : OverlappedPhysicsBalls)
	{
		if(APhysicsBall* PhysicsBall = Cast<APhysicsBall>(TestBall))
		{
			/**   */
			FindLeaderAndFollower(PhysicsBall);

			/**   */
			CalculateBehaviorForNearbyAgents(PhysicsBall);
		}
	}
}

void APhysicsBall::FindLeaderAndFollower(APhysicsBall* PhysicsBall)
{
	/** Don't follow, followers as the leader  */
	if (PhysicsBall->Leader != this)
	{
		/** If any of these conditions return True, they're already following an agent or leading another agent  */
		if (bIsLeader || Leader || Follower)
		{
			// nothing
		}
		else
		{
			/** If we don’t have a leader, and we are not one. Find one  */
			if (this != PhysicsBall->Leader && PhysicsBall->Follower)
			{
				PhysicsBall->SetFollower(this);
				Leader = PhysicsBall;
			}
		}
	}
}

void APhysicsBall::CalculateBehaviorForNearbyAgents(APhysicsBall* PhysicsBall)
{
	FVector FromOverlappedBallToThis = PhysicsBall->GetActorLocation() - GetActorLocation();
	float Clamped = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 300.f), FVector2D(1.f, 0.f), FromOverlappedBallToThis.Size());

	NAlignment += PhysicsBall->GetDirection() * Clamped;

	NCohesion += GetActorLocation() + Clamped * (PhysicsBall->GetActorLocation() - GetActorLocation());

	NSeperation += FVector::ZeroVector + Clamped *( (PhysicsBall->GetActorLocation() - GetActorLocation()) - FVector::ZeroVector);
}

void APhysicsBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && OtherActor->IsA(APhysicsBall::StaticClass()))
	{
		OverlappedPhysicsBalls.Add(OtherActor);
	}
}

void APhysicsBall::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && OtherActor->IsA(APhysicsBall::StaticClass()))
	{
		OverlappedPhysicsBalls.Remove(OtherActor);
	}
}

void APhysicsBall::ResetBall()
{
	SetActorLocation(StartLocation);

	FVector RandomUnitVector = FMath::VRand();
}

void APhysicsBall::CreateHUD(AController* NewController)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(NewController))
	{
		if (HUDWidgetClass)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
			if (CurrentWidget)
			{
				CurrentWidget->AddToViewport();
				PlayerController->bShowMouseCursor = true;
			}
		}
	}
}

void APhysicsBall::SetFollower(APhysicsBall* NewFollower)
{
	Follower = NewFollower;
}
