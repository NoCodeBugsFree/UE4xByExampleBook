// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_AvoidObstacles.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void AAIController_AvoidObstacles::BeginPlay()
{
	Super::BeginPlay();

	/** change turn direction every 2 seconds  */
	FTimerHandle ChangeTimer;
	GetWorldTimerManager().SetTimer(ChangeTimer, this, &AAIController_AvoidObstacles::InverseShouldTurnRight, 2.f, true);
}

void AAIController_AvoidObstacles::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/** start avoid obstacles distance  */
	float Distance = 250.f;
	
	FVector Direction = GetPawn()->GetActorForwardVector();
	FVector Start = GetPawn()->GetActorLocation();
	FVector End = Start + (Direction * Distance);
	
	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetPawn());
	
	bool bHasHitSomething = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Camera, CollisionQueryParams);
	
	/** if we hit the obstacle - we must avoid it  */
	if (bHasHitSomething)
	{
		/** left or right turn ?  */
		if (bShouldTurnRight)
		{
			FVector RightDirection = GetPawn()->GetActorRightVector();
			FVector RightEnd = Start + (RightDirection * Distance);
			MoveToLocation(RightEnd);
		} 
		else
		{
			FVector LeftDirection = - GetPawn()->GetActorRightVector();
			FVector LeftEnd = Start + (LeftDirection * Distance);
			MoveToLocation(LeftEnd);
		}
	}
	else /** go to the end of the line trace  */
	{
		MoveToLocation(End);
	}

	/** if we stuck go backwards */
	if (ACharacter* AICharacter = Cast<ACharacter>(GetPawn()))
	{
		if (AICharacter->GetCharacterMovement()->Velocity.Size() < 10.f)
		{
			if (bCanRotateBackwards) // DO ONCE
			{
				bCanRotateBackwards = false;
				FTimerHandle BackwardsTimer;
				GetWorldTimerManager().SetTimer(BackwardsTimer, this, &AAIController_AvoidObstacles::RotateBackwards, 1.f, false);
			}
		}
	}
}

void AAIController_AvoidObstacles::InverseShouldTurnRight()
{
	bShouldTurnRight = !bShouldTurnRight;
}

void AAIController_AvoidObstacles::RotateBackwards()
{
	bCanRotateBackwards = true;
	FRotator PawnRotation = GetPawn()->GetActorRotation();
	FRotator BackwardsRotation = PawnRotation + FRotator(0.f, 180.f, 0.f);
	GetPawn()->SetActorRotation(BackwardsRotation);
}
