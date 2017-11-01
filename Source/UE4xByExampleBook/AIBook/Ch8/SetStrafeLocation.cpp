// Fill out your copyright notice in the Description page of Project Settings.

#include "SetStrafeLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Ch8GameModeBase.h"

USetStrafeLocation::USetStrafeLocation()
{
	StrafeLocation.SelectedKeyName = "StrafeLocation";
	TargetActor.SelectedKeyName = "TargetActor";
	NodeName = FString("Set Strafe Location");
}

EBTNodeResult::Type USetStrafeLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/** if blackboard is valid  */
	if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		/** and we have a valid AI pawn  */
		if (APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn())
		{
			/**  and we have a valid enemy in blackboard */
			if (APawn* TargetActorPawn = Cast<APawn>(BlackboardComponent->GetValueAsObject(TargetActor.SelectedKeyName)))
			{
				const FVector TargetActorLocation = TargetActorPawn->GetActorLocation();
				const FVector AIPawnLocation = AIPawn->GetActorLocation();

				const FVector Center = (AIPawnLocation + TargetActorLocation) / 2.f;
				float Distance = (AIPawnLocation - TargetActorLocation).Size();
				if (Distance < 200.f)
				{
					Distance = FMath::RandRange(500.f, 1000.f);
				}
				
				FNavLocation RandomPoint;
				if (GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(Center, Distance / 2.f, RandomPoint))
				{
					BlackboardComponent->SetValueAsVector(StrafeLocation.SelectedKeyName, RandomPoint.Location);
					if (ACh8GameModeBase* Ch8GameMode = Cast<ACh8GameModeBase>(GetWorld()->GetAuthGameMode()))
					{
						Ch8GameMode->SpawnDebugActorAtLocation(RandomPoint.Location);
					}
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
