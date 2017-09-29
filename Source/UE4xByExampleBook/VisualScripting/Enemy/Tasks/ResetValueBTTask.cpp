// Fill out your copyright notice in the Description page of Project Settings.

#include "ResetValueBTTask.h"

UResetValueBTTask::UResetValueBTTask()
{
	ResetKey.SelectedKeyName = "Player";
	NodeName = FString("Reset Player BB Variable ");
}

EBTNodeResult::Type UResetValueBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/**  if Blackboard is valid */
	if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
	{
		/** nullify the  ResetKey object */
		Blackboard->SetValueAsObject(ResetKey.SelectedKeyName, nullptr);
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
