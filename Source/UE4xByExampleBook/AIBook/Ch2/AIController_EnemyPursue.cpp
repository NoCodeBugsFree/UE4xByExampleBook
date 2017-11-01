// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_EnemyPursue.h"

AAIController_EnemyPursue::AAIController_EnemyPursue()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIController_EnemyPursue::BeginPlay()
{
	Super::BeginPlay();

	TargetPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AAIController_EnemyPursue::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetPawn)
	{
		FVector PossessedPawnLocation = GetPawn()->GetActorLocation();
		FVector EnemyLocation = TargetPawn->GetActorLocation();

		FVector DirectionFromAItoCharacter = (EnemyLocation - PossessedPawnLocation).GetSafeNormal();
		FRotator XRot = FRotationMatrix::MakeFromX(DirectionFromAItoCharacter).Rotator();
		FVector Direction = XRot.Vector();
		
		FVector Destination = EnemyLocation + Direction;
		
		MoveToLocation(Destination, 50.f);
	}
}