// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AttackCharacter.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"


EBTNodeResult::Type UBTTask_AttackCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/** if AI controller is valid  */
	if (AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		/** and it has a valid pawn  */
		if (AEnemyCharacter* BearCharacter = Cast<AEnemyCharacter>(EnemyAIController->GetPawn()))
		{
			/** perform attack  */
			BearCharacter->OnPerformAttack();
			return EBTNodeResult::Succeeded;
		} 
	}

	/**  smth was wrong ...  */
	return EBTNodeResult::Failed;
}
