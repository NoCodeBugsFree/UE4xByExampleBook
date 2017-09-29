// Fill out your copyright notice in the Description page of Project Settings.

#include "VSEnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "VSEnemyCharacter.h"

AVSEnemyAIController::AVSEnemyAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));	
}

void AVSEnemyAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);
	
	/** Initialize Blackboard and Start Behavior Tree  */
	if (AVSEnemyCharacter* VSEnemyCharacter = Cast<AVSEnemyCharacter>(Pawn))
	{
		if (VSEnemyCharacter->BehaviorTree && VSEnemyCharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(VSEnemyCharacter->BehaviorTree->BlackboardAsset));
		}
		BehaviorTreeComponent->StartTree(*VSEnemyCharacter->BehaviorTree);
	}
}


