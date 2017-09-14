// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BossCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BossModeCharacter.h"
#include "BossModeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ABossAIController::ABossAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void ABossAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	
	/** if we have a valid character and BehaviorTree - init BlackBoard  */
	ControlledCharacter = Cast<ABossCharacter>(InPawn);
	if (ControlledCharacter && ControlledCharacter->BehaviorTree)
	{
		if (ControlledCharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(ControlledCharacter->BehaviorTree->BlackboardAsset));
		}

		/** Start tree and init BB keys  */
		BehaviorTreeComponent->StartTree(*ControlledCharacter->BehaviorTree);
		if (BlackboardComponent)
		{
			BossStateBlackboardKey = BlackboardComponent->GetKeyID("BossState");
			TargetBlackboardKey = BlackboardComponent->GetKeyID("TargetToFollow");
		}
	}
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ControlledCharacter)
	{
		/** if we should track character - rotate Boss towards the character  */
		if (bIsTracking && Target)
		{
			FVector CharacterLocation = ControlledCharacter->GetActorLocation();
			FVector DirectionToTarget = Target->GetActorLocation() - CharacterLocation;
			FRotator RotationToTarget = DirectionToTarget.Rotation();
			ControlledCharacter->SetActorRotation(FMath::Lerp(ControlledCharacter->GetActorRotation(), RotationToTarget, DeltaTime * 5));
		}
	}
}

void ABossAIController::TrackToTarget()
{
	if (BlackboardComponent)
	{
		/** Sets target to BB  */
		//Target = Cast<ABossModeCharacter>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TargetBlackboardKey));
		Target = Cast<ABossModeCharacter>(BlackboardComponent->GetValueAsObject("TargetToFollow")); // without initialization
		if (Target)
		{
			bIsTracking = true;
		}
	}
}

void ABossAIController::StopTrack()
{
	bIsTracking = false;
	Target = nullptr;
}

void ABossAIController::FireMissles()
{
	if (Target && ControlledCharacter)
	{
		// Find Launch points (5)
		for (int i = 1; i <= 5; ++i)
		{
			float fAngle = 16 + i * 26;
			FVector CirclePoint;
			CirclePoint.Y = (FMath::Cos(PI / 2) * FMath::Sin((fAngle * PI / 180.0f)));
			CirclePoint.Z = (FMath::Sin(PI / 2) * FMath::Sin((fAngle * PI / 180.0f)));
			CirclePoint.X = (FMath::Cos((fAngle * PI / 180.0f)));
			FRotator CharacterRotation = ControlledCharacter->GetActorRotation();
			CharacterRotation.Yaw = CharacterRotation.Yaw + 90.0f;
			CirclePoint = CharacterRotation.RotateVector(CirclePoint);
			FVector SpawnLocation = ControlledCharacter->GetActorLocation() + CirclePoint * 180.0f;
			FRotator SpawnRotation = ControlledCharacter->GetActorRotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ABossModeProjectile* BossModeProjectile = GetWorld()->SpawnActor<ABossModeProjectile>(Target->ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
			if (BossModeProjectile)
			{
				BossModeProjectile->GetProjectileMovement()->HomingTargetComponent = Cast<USceneComponent>(Target->GetComponentByClass(USceneComponent::StaticClass()));
				BossModeProjectile->GetSphereComponent()->MoveIgnoreActors.Add(ControlledCharacter);
			}
		}
	} 
}

void ABossAIController::SetStateAccordingCurrentHealth()
{
	if (ControlledCharacter && BlackboardComponent)
	{
		float Health = ControlledCharacter->GetHealth();
		if (Health < 33.f)
		{
			BossState = EBossState::BS_FINAL;
			StopMovement();
		}
		else if (Health >= 33.f && Health < 66.f)
		{
			BossState = EBossState::BS_TURRET;
			StopMovement();
		}
		else
		{
			BossState = EBossState::BS_FOLLOW;
		}

		/** sets the boss state to BB  */
		BlackboardComponent->SetValue<UBlackboardKeyType_Enum>(BossStateBlackboardKey, (uint8)BossState);
	}
}
