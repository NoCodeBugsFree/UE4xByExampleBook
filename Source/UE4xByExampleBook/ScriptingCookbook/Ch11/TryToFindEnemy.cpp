// Fill out your copyright notice in the Description page of Project Settings.

#include "TryToFindEnemy.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

UTryToFindEnemy::UTryToFindEnemy()
{
	ClosestEnemy.SelectedKeyName = "ClosestEnemy";
	NodeName = FString("Try To Find Closest Enemy");
	Interval = 10.f;
	RandomDeviation = 1.f;

	/** call Tick event when task search enters this node (SearchStart will be called as well) */
	bCallTickOnSearchStart = true;
}

void UTryToFindEnemy::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	PossessedPawn = SearchData.OwnerComp.GetAIOwner()->GetPawn();
}

void UTryToFindEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (PossessedPawn)
	{
		/* TArray is the collection that contains all the HitResults */
		TArray<FHitResult> HitResults;

		/* The Start location of the sphere */
		FVector StartLocation = PossessedPawn->GetActorLocation();
		FVector EndLocation = StartLocation;

		/* Declare the Collision Shape, assign a Sphere shape and set it's radius */
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(SearchRadius);

		FCollisionQueryParams CQP;
		CQP.AddIgnoredActor(PossessedPawn);
		CQP.bTraceComplex = false;

		FCollisionObjectQueryParams COQP(ECC_Pawn);

		/* Perform the actual raycast. This method returns true if there is at least 1 hit. */
		bool bHitSomething = GetWorld()->SweepMultiByObjectType(HitResults, StartLocation, EndLocation, FQuat::FQuat(), COQP, CollisionShape, CQP);

		/* If the raycast hit a number of objects, iterate through them and do stuff */
		if (bHitSomething)
		{
			AActor* ClosestActor = nullptr;
			float MinDistance = SearchRadius;
			for (FHitResult& Hit : HitResults) // TODO why we have to much hit results here ???
			{
				if (Hit.GetActor())
				{
					FVector Vector = StartLocation - Hit.GetActor()->GetActorLocation();
					float Distance = Vector.Size();

					if (Distance < MinDistance)
					{
						MinDistance = Distance;
						ClosestActor = Hit.GetActor();
					}
				}
			}
			/** get closest enemy and save him to blackboard */
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(ClosestEnemy.SelectedKeyName, ClosestActor);
		}
	}
}

