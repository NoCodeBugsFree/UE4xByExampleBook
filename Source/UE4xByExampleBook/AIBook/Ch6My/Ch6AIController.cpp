// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch6AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Ch6EnemyCharacter.h"


ACh6AIController::ACh6AIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void ACh6AIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);
	
	/** Initialize Blackboard and Start Behavior Tree */
	if (ACh6EnemyCharacter* Ch6EnemyCharacter = Cast<ACh6EnemyCharacter>(Pawn))
	{
		if (Ch6EnemyCharacter->BehaviorTree && Ch6EnemyCharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(Ch6EnemyCharacter->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*Ch6EnemyCharacter->BehaviorTree);
		}
	}

	/** set state to BB */
	SetState(State);
}

void ACh6AIController::SetState(ECh6EnemyState NewState)
{
	/** already dead  */
	if (State == ECh6EnemyState::ECh6_Dead)
	{
		return;
	}

	State = NewState;
	BlackboardComponent->SetValueAsEnum("State", (uint8)NewState);
}
