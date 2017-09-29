// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_SearchCharacter.h"
#include "EnemyAIController.h"

void UBTService_SearchCharacter::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/** try to retrieve AI Controller  */
	if (AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		/** if Enemy is NOT set  */
		if (!EnemyAIController->GetEnemy())
		{
			/** find him!  */
			EnemyAIController->OnSearchForEnemy();
		}
	}
}


