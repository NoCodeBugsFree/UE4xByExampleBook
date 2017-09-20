// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_RandomMoveTo.h"
#include "BossAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/Navigation/NavigationSystem.h"


EBTNodeResult::Type UBTTaskNode_RandomMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ThisTree == nullptr || ThisController == nullptr)
	{
		ThisTree = OwnerComp.GetCurrentTree();
		ThisController = Cast<ABossAIController>(OwnerComp.GetAIOwner());
		if (ThisTree == nullptr || ThisController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task assigned to incorrect AI type"));
			return EBTNodeResult::Failed;
		}
	}
	
	/** Describes a point in navigation data */
	FNavLocation RandomPoint;
	if (GetWorld()->GetNavigationSystem()->GetRandomPointInNavigableRadius(ThisController->GetPawn()->GetActorLocation(), 5000.0f, RandomPoint))
	{
		ThisController->MoveTo(RandomPoint.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
