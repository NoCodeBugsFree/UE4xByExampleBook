// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_CppMoveTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_CppMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (APawn* ControlledPawn = AIController->GetPawn())
		{
			if (OwnerComp.GetBlackboardComponent())
			{
				if (UObject* Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetToFollow.SelectedKeyName))
				{
					AActor* GoalActor = Cast<AActor>(Object);
					if (GoalActor)
					{	
						EPathFollowingRequestResult::Type PathFollowingRequestResult = AIController->MoveToActor(GoalActor, 200.f);
						switch (PathFollowingRequestResult)
						{	
							/** Failed   */
							case EPathFollowingRequestResult::Failed:
							{
								return EBTNodeResult::Failed;
								break;
							}
										
							/** AlreadyAtGoal   */
							case EPathFollowingRequestResult::AlreadyAtGoal:
							{
								return EBTNodeResult::Succeeded;
								break;
							}

							/** RequestSuccessful   */
							case EPathFollowingRequestResult::RequestSuccessful:
							{
								return EBTNodeResult::Succeeded;
								break;
							}
						
							default:
								break;
						}
					}
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
