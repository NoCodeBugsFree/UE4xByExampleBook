// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractingPawn.h"
#include "Interactable.h"
#include "DrawDebugHelpers.h"

void AInteractingPawn::TryInteract()
{
	APlayerController* MyController = Cast<APlayerController>(Controller);
	if (MyController)
	{
		APlayerCameraManager* MyCameraManager = MyController->PlayerCameraManager;
		auto StartLocation = MyCameraManager->GetCameraLocation();
		auto EndLocation = MyCameraManager->GetCameraLocation() + (MyCameraManager->GetActorForwardVector() * 100);
		FHitResult HitResult;
		GetWorld()->SweepSingleByObjectType(HitResult, StartLocation, EndLocation, FQuat::Identity,
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::AllObjects),
			FCollisionShape::MakeSphere(25),
			FCollisionQueryParams(FName("Interaction"), true, this));
		
		if (HitResult.GetActor())
		{
			DrawDebugSphere(GetWorld(), HitResult.Location, 25.f, 24, FColor::Green, false, 10.f, 0, 3.f);
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				if (IInteractable* Interactable = Cast<IInteractable>(HitResult.GetActor()))
				{
					if (Interactable->Execute_CanInteract(HitResult.GetActor()))
					{
						Interactable->Execute_PerformInteract(HitResult.GetActor());
					}
				}
			}
		}
	}
}

void AInteractingPawn::SetupPlayerInputComponent(UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);

	InInputComponent->BindAction("Interact", IE_Released, this, &AInteractingPawn::TryInteract);
}
