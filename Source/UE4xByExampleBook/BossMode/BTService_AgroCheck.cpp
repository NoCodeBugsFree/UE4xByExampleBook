// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_AgroCheck.h"
#include "BossAIController.h"
#include "BossCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"

void UBTService_AgroCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	/** if one of our pointers is NULL - try to reinitialize it  */
	if (ThisTree == NULL || ThisController == NULL || ThisAICharacter == NULL)
	{
		ThisTree = OwnerComp.GetCurrentTree();
		ThisController = Cast<ABossAIController>(OwnerComp.GetAIOwner());
		if (ThisController)
		{
			ThisAICharacter = Cast<ABossCharacter>(ThisController->GetPawn());
		}
	}
	/** one of our pointers is still NULL - LOG ERROR and exit  */
	if (ThisTree == NULL || ThisController == NULL || ThisAICharacter == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Warning Agro Service performed on invalid AI"));
		return;
	}

	// Initialize a sweep params struct with trace complex set to true
	FCollisionQueryParams SphereSweepParams(FName(TEXT("AgroCheckSweep")), true, ThisAICharacter);

	FCollisionObjectQueryParams ObjectQuery(ECC_GameTraceChannel1);
	// FCollisionObjectQueryParams ObjectQuery(ECC_Pawn);
	
	FHitResult HitOut(ForceInit);

	DrawDebugSphere(ThisAICharacter->GetWorld(), ThisAICharacter->GetActorLocation(), 1500, 12, FColor::Red, false, 4.f);

	// Perform the sweep and check boolean return, we will only be checking for BMCharacter objects
	FVector Start = ThisAICharacter->GetActorLocation();
	FVector End = ThisAICharacter->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f);
	bool bResult = ThisAICharacter->GetWorld()->SweepSingleByObjectType(HitOut, Start, End, FQuat(), ObjectQuery, FCollisionShape::MakeSphere(1500), SphereSweepParams);
	
	/** set values in BB  */
	if (bResult)
	{
		/** set received data to the BlackBoard  */
		ThisController->GetBlackboard()->SetValueAsObject(TEXT("TargetToFollow"), HitOut.GetActor());
		ThisController->GetBlackboard()->SetValueAsVector(TEXT("HomeLocation"), ThisAICharacter->GetActorLocation());
		ThisController->GetBlackboard()->SetValueAsVector(TEXT("TargetLocation"), HitOut.GetActor()->GetActorLocation());

		/** Start tracking the target character  */
		ThisController->TrackToTarget();
	}
	else
	{
		/** clear the BlackBoard  */
		ThisController->GetBlackboard()->SetValueAsObject(TEXT("TargetToFollow"), nullptr);

		/** Stop tracking the target character  */
		ThisController->StopTrack();
	}
}
