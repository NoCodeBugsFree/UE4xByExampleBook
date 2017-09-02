// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashCharacter.h"
#include "Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BountyDashTargetPoint.h"
#include "Obstacle.h"
#include "BountyDashGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Coin.h"
#include "Components/DestructibleComponent.h"
#include "Floor.h"
#include "Components/AudioComponent.h"

// Sets default values
ABountyDashCharacter::ABountyDashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}
	
	// Configure character movement
	GetCharacterMovement()->JumpZVelocity = 1450.0f;
	GetCharacterMovement()->GravityScale = 4.5f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	check(CameraBoom);
	CameraBoom->SetupAttachment(RootComponent);

	// The camera follows at this distance behind the character
	CameraBoom->TargetArmLength = 500.0f;

	// Offset to player
	CameraBoom->AddRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	check(FollowCamera);

	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::SnapToTargetIncludingScale, USpringArmComponent::SocketName);

	// Rotational change to make the camera look down slightly
	FollowCamera->AddRelativeRotation(FQuat(FRotator(-10.0f, 0.0f, 0.0f)));

	// Game Properties
	CharacterSpeed = 10.0f;

	// Poses the input at ID 0 (the default controller)
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	HitObstacleSound = CreateDefaultSubobject<UAudioComponent>(TEXT("HitSound"));
	HitObstacleSound->SetupAttachment(RootComponent);
	HitObstacleSound->bAutoActivate = false;

	DingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DingSound"));
	DingSound->SetupAttachment(RootComponent);
	DingSound->bAutoActivate = false;


}

// Called when the game starts or when spawned
void ABountyDashCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyDashCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ABountyDashCharacter::OnOverlapEnd);
	
	// fill the TargetArray
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABountyDashTargetPoint::StaticClass(), FoundActors);
	
	for (auto Actor : FoundActors)
	{
		ABountyDashTargetPoint* TestActor = Cast<ABountyDashTargetPoint>(Actor);
		if (TestActor)
		{
			TargetArray.AddUnique(TestActor);
		}
	}
	
	auto SortPred = [](const AActor& A, const AActor& B)->bool
	{
		return(A.GetActorLocation().Y < B.GetActorLocation().Y);
	};
	TargetArray.Sort(SortPred);

	/** ensure that the character starts the game in th middle most lane  */
	CurrentLocation = ((TargetArray.Num() / 2) + (TargetArray.Num() % 2) - 1);

	/** find floor actor and set the KillPoint var  */
	TArray<AActor*> FloorsActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFloor::StaticClass(), FloorsActors);
	
	if (FloorsActors.Num() > 0)
	{
		if (FloorsActors.IsValidIndex(0))
		{
			AFloor* Floor = Cast<AFloor>(FloorsActors[0]);
			if (Floor)
			{
				Killpoint = Floor->GetKillPoint();
			}
		}
	}
}

// Called every frame
void ABountyDashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetArray.Num() > 0)
	{
		FVector TargetLocation = TargetArray[CurrentLocation]->GetActorLocation();
		TargetLocation.Z = GetActorLocation().Z;
		TargetLocation.X = GetActorLocation().X;
		if (TargetLocation != GetActorLocation())
		{
			SetActorLocation(FMath::Lerp(GetActorLocation(), TargetLocation, CharacterSpeed * DeltaTime));
		}
	}

	if (bBeingPushed)
	{
		float MovementSpeed = 0.f;

		if (ABountyDashGameMode* BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode()))
		{
			MovementSpeed = BountyDashGameMode->GetInvGameSpeed();
			AddActorLocalOffset(FVector(MovementSpeed, 0.f, 0.f));
		}
	}

	if (CanMagnet)
	{
		CoinMagnet();
	}

	if (GetActorLocation().X < Killpoint)
	{
		if (ABountyDashGameMode* BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode()))
		{
			BountyDashGameMode->GameOver();
		}
	}
}

// Called to bind functionality to input
void ABountyDashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("BountyMoveRight", IE_Pressed, this, &ABountyDashCharacter::MoveRight);
	PlayerInputComponent->BindAction("BountyMoveLeft", IE_Pressed, this, &ABountyDashCharacter::MoveLeft);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Reset", IE_Pressed, this, &ABountyDashCharacter::Reset).bExecuteWhenPaused = true;
}

void ABountyDashCharacter::ScoreUp()
{
	Score++;
	ABountyDashGameMode* BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode());
	if (BountyDashGameMode)
	{
		BountyDashGameMode->CharScoreUp(Score);
	}

	if (DingSound)
	{
		DingSound->Play();
	}
}

void ABountyDashCharacter::PowerUp(EPowerUp Type)
{
	switch (Type)
	{

		case EPowerUp::SPEED:
		{	
			ABountyDashGameMode* BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode());
			if (BountyDashGameMode)
			{
				BountyDashGameMode->ReduceGameSpeed();
			}
			break;
		}

		case EPowerUp::SMASH:
		{
			CanSmash = true;
			FTimerHandle newTimer;
			GetWorld()->GetTimerManager().SetTimer(newTimer, this, &ABountyDashCharacter::StopSmash, SmashTime, false);
			break;
		}

		case EPowerUp::MAGNET:
		{
			CanMagnet = true;
			FTimerHandle newTimer;
			GetWorld()->GetTimerManager().SetTimer(newTimer, this, &ABountyDashCharacter::StopMagnet, MagnetTime, false);
			break;
		}

		default:
			break;

	}
}

void ABountyDashCharacter::MoveRight()
{
	if ((Controller))
	{
		if (CurrentLocation < TargetArray.Num() - 1)
		{
			++CurrentLocation;
		}
		else
		{
			// Do Nothing
		}
	}
}

void ABountyDashCharacter::MoveLeft()
{
	if ((Controller))
	{
		if (CurrentLocation > 0)
		{
			--CurrentLocation;
		}
		else
		{
			// Do Nothing
		}
	}
}

void ABountyDashCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		/** IsChildOf - Returns true if this struct either is class T, or is a child of class T. This will not crash on null structs */
		if (OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()))
		{
			FVector vecBetween = OtherActor->GetActorLocation() - GetActorLocation();
			float AngleBetween = FMath::Acos(FVector::DotProduct(vecBetween.GetSafeNormal(), GetActorForwardVector().GetSafeNormal()));
			AngleBetween *= (180 / PI);
			UE_LOG(LogTemp, Error, TEXT("Here"));
			if (AngleBetween < 60.0f)
			{
				if (!bBeingPushed && HitObstacleSound)
				{
					HitObstacleSound->Play();
				}

				AObstacle* Obstacle = Cast<AObstacle>(OtherActor);
				if (Obstacle && CanSmash)
				{
					Obstacle->GetDestructable()->ApplyRadiusDamage(10000.f, GetActorLocation(), 10000.f, 10000.f, true);
					UE_LOG(LogTemp, Error, TEXT("Your message"));
				}
				else
				{
					bBeingPushed = true;
				}
			}
		}
	}
}

void ABountyDashCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()))
		{
			bBeingPushed = false;
		}
	}
}

void ABountyDashCharacter::StopSmash()
{
	CanSmash = false;
}

void ABountyDashCharacter::StopMagnet()
{
	CanMagnet = false;
}

void ABountyDashCharacter::CoinMagnet()
{	
	/** find all coins and store them into the array  */
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoin::StaticClass(), FoundActors);
	TArray<ACoin*> AllCoins;
	for (auto& Actor : FoundActors)
	{
		ACoin* TestActor = Cast<ACoin>(Actor);
		if (TestActor)
		{
			AllCoins.AddUnique(TestActor);
		}
	}

	/** for each coin -> Move coin towards character if needed  */
	for (auto& Coin : AllCoins)
	{
		FVector Between = GetActorLocation() - Coin->GetActorLocation();
		if (FMath::Abs(Between.Size()) < MagnetReach)
		{
			FVector CoinPosition = FMath::Lerp(Coin->GetActorLocation(), GetActorLocation(), 0.2f);
			Coin->SetActorLocation(CoinPosition);
			Coin->BeingPulled = true;
		}
	}
}

void ABountyDashCharacter::Reset()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BountyDashMap"));
}

