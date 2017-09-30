// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAttack.h"
#include "VisualScripting/VSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "VisualScripting/Enemy/VSEnemyCharacter.h"
#include "AIController.h"

UMyAttack::UMyAttack()
{
	/** intended defaults  */
	ActorToDamage.SelectedKeyName = "Player";
}

EBTNodeResult::Type UMyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/**  if blackboard is valid */
	if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
	{
		/** and ActorToDamage is valid  */
		if (AVSCharacter* VSCharacter = Cast<AVSCharacter>(Blackboard->GetValueAsObject(ActorToDamage.SelectedKeyName)))
		{
			// -------- Book way ----------------------------------------------------------
			/** damage VSCharacter  */
			// VSCharacter->TakeDamage(Damage, FDamageEvent(), OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn());
			// -------- Book way ----------------------------------------------------------

			/** use animations to damage the player  */
			if (AVSEnemyCharacter* VSEnemyCharacter = Cast<AVSEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
			{
				VSEnemyCharacter->Attack();
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
