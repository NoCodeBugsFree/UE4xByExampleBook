// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIMeleeController.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AAIMeleeController : public AAIController
{
	GENERATED_BODY()
	
public:
	
protected:

	AAIMeleeController();

	virtual void Possess(APawn* Pawn) override;

private:

	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	/** Blackboard Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;
	
	/** BehaviorTree Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	
};
