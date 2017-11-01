// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AgroCheck.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UBTService_AgroCheck : public UBTService
{
	GENERATED_BODY()
	
private:

	UBTService_AgroCheck();

	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	class UBehaviorTree* ThisTree;

	class ABossAIController* ThisController;
	
	class ABossCharacter* ThisAICharacter;
	
};

