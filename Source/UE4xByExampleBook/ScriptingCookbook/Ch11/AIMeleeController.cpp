// Fill out your copyright notice in the Description page of Project Settings.

#include "AIMeleeController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ConstructorHelpers.h"

AAIMeleeController::AAIMeleeController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	
	auto BT = static ConstructorHelpers::FObjectFinder<UBehaviorTree>(TEXT("BehaviorTree'/Game/ScriptingCookbook/Ch11/BT_MeleeAttacker.BT_MeleeAttacker'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void AAIMeleeController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	/** Initialize Blackboard and Start Behavior Tree */
	if (Pawn && BehaviorTree && BehaviorTree->BlackboardAsset)
	{
		BlackboardComponent->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}