// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ResetHeardPlayerBTTask.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UResetHeardPlayerBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	/** aborts this task, should return Aborted or InProgress
	*  (use FinishLatentAbort() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
private:

	UResetHeardPlayerBTTask();
	
	/** Has Heard Sound Blackboard Key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector HasHeardSound; 

	/** Location Of Sound Blackboard Key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LocationOfSound;

	/** state to set HasHeardSound key after execute or abort this task */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool NewHasHeardSoundState = false;
		
	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
