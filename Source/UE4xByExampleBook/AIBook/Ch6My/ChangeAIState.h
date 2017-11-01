// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Ch6AIController.h"
#include "ChangeAIState.generated.h"

/**
 * 
 */

UCLASS()
class UE4XBYEXAMPLEBOOK_API UChangeAIState : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	UChangeAIState();

	/** Target To Follow Blackboard Key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector AIState;

	/** Target To Follow Blackboard Key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	ECh6EnemyState RequiredState = ECh6EnemyState::ECh6_Wander;
	
	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	 
};
