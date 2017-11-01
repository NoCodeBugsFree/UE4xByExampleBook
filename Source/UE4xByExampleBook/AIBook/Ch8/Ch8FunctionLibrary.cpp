// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch8FunctionLibrary.h"
#include "DrawDebugHelpers.h"

AActor* UCh8FunctionLibrary::LaserFromController(AController* TheController)
{
	if (TheController)
	{
		if(APawn* Pawn = TheController->GetPawn())
		{
			const float Distance = 99999.f;

			FVector Start = Pawn->GetActorLocation();
			FVector End = Start + Pawn->GetActorForwardVector() * Distance;

			FHitResult Hit;
			FCollisionObjectQueryParams ObjectQueryParams(ECollisionChannel::ECC_Pawn);
			FCollisionQueryParams CollisionQueryParams;
			CollisionQueryParams.AddIgnoredActor(Pawn);
			DrawDebugLine(Pawn->GetWorld(), Start, End, FColor::Red, false, 0.1f, 0, 3.f);
			Pawn->GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams, CollisionQueryParams);
			
			if (AActor* Victim = Hit.GetActor())
			{
				Victim->TakeDamage(1.f, FDamageEvent(), TheController, Pawn);
				return Victim;
			}
		}
	}
	return nullptr;
}
