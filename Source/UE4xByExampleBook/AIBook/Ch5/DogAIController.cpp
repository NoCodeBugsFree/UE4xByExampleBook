// Fill out your copyright notice in the Description page of Project Settings.

#include "DogAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DogCharacter.h"

ADogAIController::ADogAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void ADogAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	/** Initialize Blackboard and Start Behavior Tree  */
	if (ADogCharacter* DogCharacter = Cast<ADogCharacter>(Pawn))
	{
		if (DogCharacter->BehaviorTree && DogCharacter->BehaviorTree->BlackboardAsset)
		{
			RunBehaviorTree(DogCharacter->BehaviorTree);
			//BlackboardComponent->InitializeBlackboard(*(DogCharacter->BehaviorTree->BlackboardAsset));
			//BehaviorTreeComponent->StartTree(*DogCharacter->BehaviorTree);
			BlackboardComponent->SetValueAsEnum("DogState", (uint8)DogCharacter->GetDogState());
		}	
	}
}
