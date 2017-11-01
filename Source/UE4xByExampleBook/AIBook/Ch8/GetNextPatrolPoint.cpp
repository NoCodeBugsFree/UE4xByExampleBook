// Fill out your copyright notice in the Description page of Project Settings.

#include "GetNextPatrolPoint.h"
#include "Ch8AIController.h"
#include "Ch8TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

UGetNextPatrolPoint::UGetNextPatrolPoint()
{
	PatrolPoint.SelectedKeyName = "PatrolPoint";
	NodeName = FString("Find Next Patrol Point"); 
}

EBTNodeResult::Type UGetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(ACh8AIController* Ch8AiController = Cast<ACh8AIController>(OwnerComp.GetAIOwner()))
	{
		if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
		{
			/** desired target point  */
			ACh8TargetPoint* NextTargetPoint = Ch8AiController->GetRandomTargetPoint();
			
			BlackboardComponent->SetValueAsObject(PatrolPoint.SelectedKeyName, NextTargetPoint);

			return EBTNodeResult::Succeeded;
		}	
	}
	return EBTNodeResult::Failed;
}
