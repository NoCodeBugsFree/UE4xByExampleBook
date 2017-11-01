// Fill out your copyright notice in the Description page of Project Settings.

#include "ChangeAIState.h"
#include "BehaviorTree/BlackboardComponent.h"


UChangeAIState::UChangeAIState()
{
	AIState.SelectedKeyName = "State";
	NodeName = FString("Change AI State");
}

EBTNodeResult::Type UChangeAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(ACh6AIController* Ch6AIController = Cast<ACh6AIController>(OwnerComp.GetAIOwner()))
	{
		Ch6AIController->SetState(RequiredState);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
