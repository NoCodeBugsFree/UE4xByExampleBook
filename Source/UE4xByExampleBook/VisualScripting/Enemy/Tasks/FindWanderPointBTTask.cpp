// Fill out your copyright notice in the Description page of Project Settings.

#include "FindWanderPointBTTask.h"
#include "AI/Navigation/NavigationSystem.h"
#include "VisualScripting/Enemy/VSEnemyAIController.h"

UFindWanderPointBTTask::UFindWanderPointBTTask()
{
	WanderLocation.SelectedKeyName = "WanderLocation";
	NodeName = FString("Find Wander Point");
}

EBTNodeResult::Type UFindWanderPointBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/**  if AI controller is valid */
	if (AVSEnemyAIController* VSEnemyAIController = Cast<AVSEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		/** and if it has a valid pawn  */
		if (APawn* AIPawn = VSEnemyAIController->GetPawn())
		{
			FVector CurrentEnemyLocation = AIPawn->GetActorLocation();
			
			// Get Random Point In Navigable Radius
			FNavLocation RandomPoint;
			if (GetWorld()->GetNavigationSystem()->GetRandomPointInNavigableRadius(CurrentEnemyLocation, WanderRadius, RandomPoint))
			{	
				/** get the Location from  FNavLocation struct */
				FVector LocationToWander = RandomPoint.Location;

				if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
				{
					/** set  LocationToWander to blackboard */
					Blackboard->SetValueAsVector(WanderLocation.SelectedKeyName, LocationToWander);

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
