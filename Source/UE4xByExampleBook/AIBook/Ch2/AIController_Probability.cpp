// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_Probability.h"
#include "AI/Navigation/NavigationSystem.h"

void AAIController_Probability::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	FTimerHandle MoveToTimer;

	GetWorldTimerManager().SetTimer(MoveToTimer, this, &AAIController_Probability::MoveToNextRandomPoint, 1.f, true);
}

void AAIController_Probability::MoveToNextRandomPoint()
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
