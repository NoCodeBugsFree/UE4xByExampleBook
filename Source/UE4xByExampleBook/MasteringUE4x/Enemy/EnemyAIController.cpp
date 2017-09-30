// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "MasteringUE4x/Gladiator.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "EnemyCharacter.h"
#include "EngineUtils.h"

AEnemyAIController::AEnemyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	
	/** Specifies if this AI wants its own PlayerState. */
	bWantsPlayerState = true;
}

void AEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	/** calls to initialize blackboard and start behavior tree  */
	InitBlackBoardandStartBehaviorTree(InPawn);
}

void AEnemyAIController::InitBlackBoardandStartBehaviorTree(APawn* InPawn)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(InPawn);
	if (EnemyCharacter && EnemyCharacter->BehaviorTree && EnemyCharacter->BehaviorTree->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*EnemyCharacter->BehaviorTree->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyPositionKeyID = BlackboardComp->GetKeyID("EnemyPosition");

		BehaviorComp->StartTree(*EnemyCharacter->BehaviorTree);
	}
}

void AEnemyAIController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

void AEnemyAIController::SetEnemy(APawn* InPawn)
{
	if (BlackboardComp && InPawn)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);

		BlackboardComp->SetValueAsVector("EnemyPosition", InPawn->GetActorLocation());

		SetFocus(InPawn);
	}
}

class AGladiator* AEnemyAIController::GetEnemy() const
{
	if (BlackboardComp)
	{
		return Cast<AGladiator>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}
	return nullptr;
}

void AEnemyAIController::UpdateControllerRotation(float DeltaTime, bool bUpdatePawn)
{
	// Look toward focus
	FVector TheCenter = GetFocalPoint();
	if (!TheCenter.IsZero() && GetPawn())
	{
		FVector Direction = TheCenter - GetPawn()->GetActorLocation();
		FRotator TheNewRotation = Direction.Rotation();
		TheNewRotation.Yaw = FRotator::ClampAxis(TheNewRotation.Yaw);
		SetControlRotation(TheNewRotation);
		APawn* const Pawn = GetPawn();
		if (Pawn && bUpdatePawn)
		{
			Pawn->FaceRotation(TheNewRotation, DeltaTime);
		}
	}
}

bool AEnemyAIController::PawnCanBeSeen(APawn* Target)
{
	return true;
}

void AEnemyAIController::OnSearchForEnemy()
{	
	if (!GetPawn())
	{
		return;
	}

	const FVector TempLocation = GetPawn()->GetActorLocation();
	float BestDistSquared = MAX_FLT;

	AGladiator* PlayerPawn = NULL;

	// ActorIterator
	for (TActorIterator<AGladiator> It(GetWorld()); It; ++It)
	{
		if ((*It))
		{
			if (PawnCanBeSeen(*It))
			{
				AGladiator* TestPawn = Cast<AGladiator>(*It);
				AEnemyCharacter* const EnemyCharacter = Cast<AEnemyCharacter>(TestPawn);
				if (EnemyCharacter)
				{
					//it is just another enemy, not player
				}
				else
				{
					if (TestPawn && TestPawn->GetIsStillAlive())
					{
						UE_LOG(LogClass, Log, TEXT(" ===================>>>>> ENEMY SEEN %s "), *GetNameSafe(*It));

						const float DistanceSquared = (TestPawn->GetActorLocation() - TempLocation).SizeSquared();
						if (DistanceSquared < BestDistSquared)
						{
							BestDistSquared = DistanceSquared;
							PlayerPawn = TestPawn;
						}
					}
				}
			}
		}	
	}
	if (PlayerPawn)
	{
		// We saw someone, so set him as target.
		SetEnemy(PlayerPawn);
		UE_LOG(LogClass, Log, TEXT(" ===================>>>>> SetTarget"));
	}
}
