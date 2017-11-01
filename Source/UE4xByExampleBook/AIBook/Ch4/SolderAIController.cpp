// Fill out your copyright notice in the Description page of Project Settings.

#include "SolderAIController.h"
#include "WayPoint.h"
#include "EngineUtils.h"
#include "SolderAICharacter.h"

void ASolderAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	/** for all way points in the world */
	for (TActorIterator<AWayPoint> Iter(GetWorld()); Iter; ++Iter)
	{
		/** if way point is valid  */
		if ((*Iter))
		{
			/** and contains our pawn in  AllowedAccess array */
			if ((*Iter)->AllowedAccess.Contains(Cast<ASolderAICharacter>(this->GetPawn())))
			{
				/** add this way point to PatrolPoints array   */
				PatrolPoints.Add(*Iter);
			}
		}
	}
}

void ASolderAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PatrolPoints.Num() > 0)
	{
		auto Result = MoveToActor(PatrolPoints[NextPatrolPointNumber]);

		if (Result == EPathFollowingRequestResult::Type::AlreadyAtGoal)
		{
			/** change patrol point  */
			if (bCanChangePP)
			{
				bCanChangePP = false;
				int PreviousPP = NextPatrolPointNumber;
				NextPatrolPointNumber = FMath::RandRange(0, PatrolPoints.Num() - 1);

				/** not intended to move twice to the same PP  */
				if (PreviousPP == NextPatrolPointNumber)
				{
					bCanChangePP = true;
					return;
				}
				
				/** reset bCanChangePP flag by timer  */
				FTimerHandle ChangePPTimer;
				GetWorldTimerManager().SetTimer(ChangePPTimer, this, &ASolderAIController::ResetCanChangePP, 1.f, false);
			}
		}
	}
}

void ASolderAIController::ResetCanChangePP()
{
	bCanChangePP = true;
}
