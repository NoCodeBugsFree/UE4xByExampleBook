// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch8AIController.h"
#include "Ch8FunctionLibrary.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Ch8Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "EngineUtils.h"
#include "Ch8TargetPoint.h"

ACh8AIController::ACh8AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void ACh8AIController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/** find each target point in the world and store them into the array  */
	for (TActorIterator<ACh8TargetPoint> Iter(GetWorld()); Iter; ++Iter)
	{
		if ((*Iter))
		{
			TargetPoints.Add(*Iter);
		}
	}
}

void ACh8AIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	if (ACh8Character* AICharacter = Cast<ACh8Character>(GetPawn()))
	{
		if (AICharacter->BehaviorTree && AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*AICharacter->BehaviorTree);
		}
	}
}

void ACh8AIController::BeginPlay()
{
	Super::BeginPlay();

	/** sets state to bb  */
	SetAiState(AiState);
}

void ACh8AIController::OnUpdatePerception(TArray<AActor*> UpdatedActors)
{
	if (UpdatedActors.Num() > 0)
	{
		if (UpdatedActors.IsValidIndex(0))
		{
			if (ACh8Character* Ch8Character = Cast<ACh8Character>(UpdatedActors[0]))
			{
				BlackboardComponent->SetValueAsObject("TargetActor", Ch8Character);
			}
		}
	}
}

class ACh8TargetPoint* ACh8AIController::GetRandomTargetPoint() const
{
	/** start patrolling if we have at least two patrol points  */
	if (TargetPoints.Num() >= 2)
	{
		int32 RandomIndex = FMath::RandRange(0, TargetPoints.Num() - 1); // zero based array
		if (TargetPoints.IsValidIndex(RandomIndex))
		{
			return TargetPoints[RandomIndex];
		}
	}
	return nullptr;
}

void ACh8AIController::SetAiState(ECh8EnemyAiState NewState)
{
	AiState = NewState;
	BlackboardComponent->SetValueAsEnum(AiStateName, (uint8)AiState);
}
