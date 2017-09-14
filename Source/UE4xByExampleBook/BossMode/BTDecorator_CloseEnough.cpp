// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_CloseEnough.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_CloseEnough::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	/** if we have a valid AI controller  */
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		/** and a valid controlled Pawn  */
		if (APawn* ControlledPawn = AIController->GetPawn())
		{
			/** Get first needed location  */
			FVector ControlledPawnLocation = ControlledPawn->GetActorLocation();
			
			/** Get second needed location  */
			if (OwnerComp.GetBlackboardComponent())
			{
				if (UObject* Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetToFollow.SelectedKeyName))
				{
					AActor* TargetActor = Cast<AActor>(Object);
					if (TargetActor)
					{
						FVector TargetActorLocation = TargetActor->GetActorLocation();

						/** Distance check  */
						FVector TargetVector = ControlledPawnLocation - TargetActorLocation;
						if (TargetVector.Size() >= AcceptableDistance)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
