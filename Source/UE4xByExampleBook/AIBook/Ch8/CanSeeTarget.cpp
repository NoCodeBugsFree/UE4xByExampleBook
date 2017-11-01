// Fill out your copyright notice in the Description page of Project Settings.

#include "CanSeeTarget.h"
#include "Ch8Character.h"
#include "Ch8AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCanSeeTarget::UCanSeeTarget()
{
	TargetActor.SelectedKeyName = "TargetActor";
	LastTargetLocation.SelectedKeyName = "LastTargetLocation";
	NodeName = FString("Can See Target ?");
	FlowAbortMode = EBTFlowAbortMode::Self;
}

bool UCanSeeTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if(ACh8AIController* Ch8AiController = Cast<ACh8AIController>(OwnerComp.GetAIOwner()))
	{
		if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
		{
			if (ACh8Character* Enemy = Cast<ACh8Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActor.SelectedKeyName)))
			{
				const bool bCanSee = Ch8AiController->LineOfSightTo(Enemy);
				if (bCanSee)
				{
					/** store last seen location  */
					BlackboardComponent->SetValueAsVector(LastTargetLocation.SelectedKeyName, Enemy->GetActorLocation());

					/** can see  */
					return true;
				}
				BlackboardComponent->SetValueAsObject(TargetActor.SelectedKeyName, nullptr);
			}
		}
	}

	/** can't see  */
	return false;
}
