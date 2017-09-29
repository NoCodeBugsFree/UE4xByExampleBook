// Fill out your copyright notice in the Description page of Project Settings.

#include "ResetHeardPlayerBTTask.h"

UResetHeardPlayerBTTask::UResetHeardPlayerBTTask()
{
	NodeName = FString("Reset Heard Player");
	LocationOfSound.SelectedKeyName = "LocationOfSound";
	HasHeardSound.SelectedKeyName = "HasHeardSound";
}

EBTNodeResult::Type UResetHeardPlayerBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasHeardSound.SelectedKeyName, NewHasHeardSoundState);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(LocationOfSound.SelectedKeyName, FVector::ZeroVector);

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UResetHeardPlayerBTTask::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasHeardSound.SelectedKeyName, NewHasHeardSoundState);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(LocationOfSound.SelectedKeyName, FVector::ZeroVector);

	return EBTNodeResult::Aborted;
}

