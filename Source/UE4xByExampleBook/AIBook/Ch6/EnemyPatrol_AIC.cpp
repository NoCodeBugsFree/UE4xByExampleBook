// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPatrol_AIC.h"
#include "WayPointCh6.h"
#include "EngineUtils.h"
#include "EnemyPatrolCharacter.h"

void AEnemyPatrol_AIC::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	/** store the way points  */
	FillWayPoints();

	/** check way points array  */
	if (WayPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No WayPoints"));
		return;
	}

	/** initialize the current way point  */
	SetNextWayPoint();

	/** set the possessed pawn reference  */
	if(AEnemyPatrolCharacter* TestPatrolCharacter = Cast<AEnemyPatrolCharacter>(GetPawn()))
	{
		EnemyPatrolCharacter = TestPatrolCharacter;
	}
}

void AEnemyPatrol_AIC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	EAIState CurrentAIState = EnemyPatrolCharacter ? EnemyPatrolCharacter->GetState() : EAIState::AS_Dead;
	
	/** if we have a next way point and we are patrolling  */
	if (CurrentWayPoint && CurrentAIState == EAIState::AS_Patrol)
	{
		auto Result = MoveToActor(CurrentWayPoint);
		if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			/** we haven't way point for short period of time  */
			CurrentWayPoint = nullptr;
			
			/** delay  */
			FTimerHandle Timer;
			GetWorldTimerManager().SetTimer(Timer, this, &AEnemyPatrol_AIC::SetNextWayPoint, FMath::RandRange(0.5f, 1.f), false);
		}
	}
}

void AEnemyPatrol_AIC::FillWayPoints()
{
	for (TActorIterator<AWayPointCh6> Iter(GetWorld()); Iter; ++Iter)
	{
		if ((*Iter))
		{
			WayPoints.Add(*Iter);
		}
	}
}

void AEnemyPatrol_AIC::SetNextWayPoint()
{
	int32 RandomIndex = FMath::RandRange(0, WayPoints.Num() - 1);

	if (WayPoints.IsValidIndex(RandomIndex))
	{
		CurrentWayPoint = WayPoints[RandomIndex];
	}
}