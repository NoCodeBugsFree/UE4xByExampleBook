// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ResetValueBTTask.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UResetValueBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	UResetValueBTTask();

	/** Target To reset by this task */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector ResetKey;
	
	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
