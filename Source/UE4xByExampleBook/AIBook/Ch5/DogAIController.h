// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DogAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ADogAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	ADogAIController();

	/** Initialize Blackboard and Start Behavior Tree  */
	void Possess(APawn* Pawn) override;

private:

	/** Blackboard Component  */
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent;

	/** BehaviorTree Component  */
	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorTreeComponent;

public:

	/** retunrs Blackboard Component **/
	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	
	
};
