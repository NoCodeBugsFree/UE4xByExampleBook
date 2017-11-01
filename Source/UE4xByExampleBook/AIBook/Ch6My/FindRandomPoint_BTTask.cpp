// Fill out your copyright notice in the Description page of Project Settings.

#include "FindRandomPoint_BTTask.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Ch6AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindRandomPoint_BTTask::UFindRandomPoint_BTTask()
{
	WanderPoint.SelectedKeyName = "RandomPoint";
	NodeName = FString("Find Random Point"); 
}

EBTNodeResult::Type UFindRandomPoint_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ACh6AIController* Ch6AIController = Cast<ACh6AIController>(OwnerComp.GetAIOwner()))
	{
		// Get Random Point In Navigable Radius
		FNavLocation RandomPoint;
		if (GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(Ch6AIController->GetPawn()->GetActorLocation(), SearchRadius, RandomPoint))
		{
			if(UBlackboardComponent* BlackboardComponent = Cast<UBlackboardComponent>(Ch6AIController->GetBlackboardComponent()))
			{
				BlackboardComponent->SetValueAsVector(WanderPoint.SelectedKeyName, RandomPoint.Location);
			}
			return EBTNodeResult::Succeeded;
		}	
	}
	return EBTNodeResult::Failed;
}