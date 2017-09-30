// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPickup.h"
#include "VSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AAmmoPickup::AAmmoPickup()
{
	SetRootComponent(GetStaticMeshComponent());

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
}

void AAmmoPickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddDynamic(this, &AAmmoPickup::OnOverlap);
}

void AAmmoPickup::OnOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	if (OtherActor && !IsPendingKill() && OtherActor->GetClass()->IsChildOf(AVSCharacter::StaticClass()))
	{
		if (AVSCharacter* VSCharacter = Cast<AVSCharacter>(OtherActor))
		{
			/** add ammo to character  */
			VSCharacter->AddAmmo(AmmoToAdd);
	
			// try and play the sound if specified
			if (CollectSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());
			}

			Destroy();
		}
	}
}
