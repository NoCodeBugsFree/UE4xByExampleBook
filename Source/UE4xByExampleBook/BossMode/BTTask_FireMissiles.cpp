// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FireMissiles.h"
#include "BossAIController.h"

EBTNodeResult::Type UBTTask_FireMissiles::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABossAIController* BossAIController =  Cast<ABossAIController>(OwnerComp.GetAIOwner());
	if (BossAIController)
	{
		BossAIController->FireMissles();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
