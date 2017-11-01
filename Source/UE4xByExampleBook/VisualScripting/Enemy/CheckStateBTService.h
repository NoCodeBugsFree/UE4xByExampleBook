// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckStateBTService.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UCheckStateBTService : public UBTService
{
	GENERATED_BODY()
	
private:

	UCheckStateBTService();
	
	/** EnemyState blackboard key  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector EnemyState; 
	
	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
