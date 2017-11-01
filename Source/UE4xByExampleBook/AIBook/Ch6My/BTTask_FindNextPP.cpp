// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindNextPP.h"
#include "Ch6AIController.h"
#include "Ch6EnemyCharacter.h"
#include "Ch6TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNextPP::UBTTask_FindNextPP()
{
	NextPatrolPoint.SelectedKeyName = "NextPatrolPoint";
	NodeName = FString("Find Next Patrol Point");
}

EBTNodeResult::Type UBTTask_FindNextPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(ACh6AIController* Ch6AIController = Cast<ACh6AIController>(OwnerComp.GetAIOwner()))
	{
		if(ACh6EnemyCharacter* Ch6EnemyCharacter = Cast<ACh6EnemyCharacter>(Ch6AIController->GetPawn()))
		{
			if(ACh6TargetPoint* CurrentCh6TargetPoint = Ch6EnemyCharacter->GetCurrentPatrolPoint())
			{
				ACh6TargetPoint* NextCh6TargetPoint = CurrentCh6TargetPoint->GetNextTargetPoint();
				if (NextCh6TargetPoint)
				{
					/** self check  */
					if (CurrentCh6TargetPoint == NextCh6TargetPoint)
					{
						/** we are stuck at same target point - start wandering */
						Ch6AIController->SetState(ECh6EnemyState::ECh6_Wander);
					}

					/** update BB data */
					Ch6AIController->GetBlackboardComponent()->SetValueAsObject(NextPatrolPoint.SelectedKeyName, NextCh6TargetPoint);

					/** update characters data  */
					Ch6EnemyCharacter->SetCurrentPatrolPoint(NextCh6TargetPoint);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		/** Failed  */
		Ch6AIController->SetState(ECh6EnemyState::ECh6_Wander);
	}
	
	return EBTNodeResult::Failed;
}
