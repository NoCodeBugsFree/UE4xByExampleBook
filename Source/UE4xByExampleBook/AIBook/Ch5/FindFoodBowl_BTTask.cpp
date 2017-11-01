// Fill out your copyright notice in the Description page of Project Settings.

#include "FindFoodBowl_BTTask.h"
#include "FoodbowlTargetPoint.h"
#include "EngineUtils.h"
#include "DogAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindFoodBowl::UBTTask_FindFoodBowl()
{
	FoodBowl.SelectedKeyName = "FoodBowl";
	NodeName = FString("Find Food Bowl");
}

EBTNodeResult::Type UBTTask_FindFoodBowl::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/** find food bowl and store it in BB  */
	for (TActorIterator<AFoodbowlTargetPoint> Iter(GetWorld()); Iter; ++Iter)
	{
		if(AFoodbowlTargetPoint* FoodbowlTargetPoint = Cast<AFoodbowlTargetPoint>(*Iter))
		{
			if(ADogAIController* DogAIController = Cast<ADogAIController>(OwnerComp.GetAIOwner()))
			{
				if (UBlackboardComponent* BB = DogAIController->GetBlackboardComponent())
				{
					BB->SetValueAsObject(FoodBowl.SelectedKeyName, FoodbowlTargetPoint);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
