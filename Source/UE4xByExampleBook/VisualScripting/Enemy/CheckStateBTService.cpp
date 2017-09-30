// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckStateBTService.h"
#include "VSEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCheckStateBTService::UCheckStateBTService()
{
	EnemyState.SelectedKeyName = "State";
	NodeName = FString("Set Enemy State");
}

void UCheckStateBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (OwnerComp.GetAIOwner())
	{
		if (AVSEnemyCharacter* VSEnemyCharacter = Cast<AVSEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
		{
			/** get state  */
			EEnemyState CurrentEnemyState = VSEnemyCharacter->GetEnemyState();

			/** set state to blackboard  */
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)CurrentEnemyState);
		}
	}
}
