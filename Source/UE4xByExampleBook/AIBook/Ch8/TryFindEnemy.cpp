// Fill out your copyright notice in the Description page of Project Settings.

#include "TryFindEnemy.h"
#include "AI/Navigation/NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTryFindEnemy::UTryFindEnemy()
{
	LastTargetLocation.SelectedKeyName = "LastTargetLocation";
	NodeName = FString("Try Find Enemy");
}

EBTNodeResult::Type UTryFindEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		const FVector PawnLocation = Pawn->GetActorLocation();
		FNavLocation RandomPoint;
		if (GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(PawnLocation, FMath::RandRange(MinDistance, MaxDistance), RandomPoint))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(LastTargetLocation.SelectedKeyName, RandomPoint.Location);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
