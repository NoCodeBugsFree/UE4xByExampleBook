// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackAtMidRange.h"
#include "Ch8FunctionLibrary.h"
#include "Ch8AIController.h"

UAttackAtMidRange::UAttackAtMidRange()
{
	NodeName = FString("Attack Enemy At Mid Range");
}

 EBTNodeResult::Type UAttackAtMidRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
	 if (ACh8AIController* Ch8AiController = Cast<ACh8AIController>(OwnerComp.GetAIOwner()))
	 {
		 UCh8FunctionLibrary::LaserFromController(Ch8AiController);
		 return  EBTNodeResult::Succeeded;
	 }
	 return EBTNodeResult::Aborted;
 }