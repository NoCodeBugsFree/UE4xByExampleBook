// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_RandomMoveTo.h"
#include "AI/Navigation/NavigationSystem.h"

void AAIController_RandomMoveTo::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	FTimerHandle MoveToTimer;

	GetWorldTimerManager().SetTimer(MoveToTimer, this, &AAIController_RandomMoveTo::MoveToNextRandomPoint, 1.f, true);
}

void AAIController_RandomMoveTo::MoveToNextRandomPoint()
{
	if (GetPawn())
	{
		FVector PossessedPawnLocation = GetPawn()->GetActorLocation();

		FNavLocation RandomPoint;

		if (GetWorld()->GetNavigationSystem()->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), 1000.0f, RandomPoint))
		{
			FVector Destination = RandomPoint.Location;

			MoveToLocation(Destination, 100.f);
		}
	}
}
