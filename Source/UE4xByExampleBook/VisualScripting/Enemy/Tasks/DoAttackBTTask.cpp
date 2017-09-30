// Fill out your copyright notice in the Description page of Project Settings.

#include "DoAttackBTTask.h"
#include "VisualScripting/VSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UDoAttackBTTask::UDoAttackBTTask()
{
	/** intended defaults  */
	ActorToDamage.SelectedKeyName = "Player";
}

EBTNodeResult::Type UDoAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/**  if blackboard is valid */
	if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
	{
		/** and ActorToDamage is valid  */
		if (AVSCharacter* VSCharacter = Cast<AVSCharacter>(Blackboard->GetValueAsObject(ActorToDamage.SelectedKeyName)))
		{
			// -------- Book way ----------------------------------------------------------
			/** damage him  */
			VSCharacter->TakeDamage(Damage, FDamageEvent(), OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn());
			// -------- Book way ----------------------------------------------------------
			
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
