// Fill out your copyright notice in the Description page of Project Settings.

#include "FindPatrolPointBTTask.h"
#include "VisualScripting/Enemy/VSEnemyCharacter.h"

UFindPatrolPointBTTask::UFindPatrolPointBTTask()
{
	PatrolPoint.SelectedKeyName = "NextPatrolPoint";
}

EBTNodeResult::Type UFindPatrolPointBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/** try to get random patrol point and set in in blackboard  */
	if (AVSEnemyCharacter* VSEnemyCharacter = Cast<AVSEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
		{
			Blackboard->SetValueAsObject(PatrolPoint.SelectedKeyName, VSEnemyCharacter->GetRandomPatrolPoint());
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
