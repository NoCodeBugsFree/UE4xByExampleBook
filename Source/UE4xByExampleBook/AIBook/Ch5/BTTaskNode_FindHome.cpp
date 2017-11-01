// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_FindHome.h"
#include "EngineUtils.h"
#include "DogAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DogHouseTargetPoint.h"

UBTTaskNode_FindHome::UBTTaskNode_FindHome()
{
	DogHouse.SelectedKeyName = "DogHouse";
	NodeName = FString("Find Dog House");
}

EBTNodeResult::Type UBTTaskNode_FindHome::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/** find food bowl and store it in BB  */
	for (TActorIterator<ADogHouseTargetPoint> Iter(GetWorld()); Iter; ++Iter)
	{
		if (ADogHouseTargetPoint* DogHouseTargetPoint = Cast<ADogHouseTargetPoint>(*Iter))
		{
			if (ADogAIController* DogAIController = Cast<ADogAIController>(OwnerComp.GetAIOwner()))
			{
				if (UBlackboardComponent* BB = DogAIController->GetBlackboardComponent())
				{
					BB->SetValueAsObject(DogHouse.SelectedKeyName, DogHouseTargetPoint);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
