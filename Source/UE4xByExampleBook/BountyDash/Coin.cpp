// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "BountyDashCharacter.h"
#include "BountyDashGameMode.h"
#include "Components/SphereComponent.h"
#include "Obstacle.h"
#include "BountyDashParticle.h"

ACoin::ACoin()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");
}

void ACoin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Mesh->AddLocalRotation(FRotator(0.0f, 5.0f, 0.0f));
}

void ACoin::MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	/** We need to detect if the
		coin is currently colliding with an obstacle. If so, we need to adjust the height of the
		coin object 
	 */
	if (OtherActor && OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()) && !BeingPulled)
	{
		USphereComponent* ThisSphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
		USphereComponent* OtherSphere = Cast<USphereComponent>(OtherActor->GetComponentByClass(USphereComponent::StaticClass()));
		if (OtherSphere)
		{
			AddActorLocalOffset(FVector(0.0f, 0.0f, (OtherSphere->GetUnscaledSphereRadius() * 2.0f) + Collider->GetUnscaledSphereRadius()));
		}
	}

	if (OtherActor && OtherActor->GetClass()->IsChildOf(ABountyDashCharacter::StaticClass()) && !IsPendingKill())
	{
		ABountyDashCharacter* BountyDashCharacter = Cast<ABountyDashCharacter>(OtherActor);
		if (BountyDashCharacter)
		{
			// Spawn Actor
			if (WhatToSpawn)
			{
				UWorld* const World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = Instigator;

					FVector Location = BountyDashCharacter->GetActorLocation();
					FRotator Rotation = FRotator::ZeroRotator;
					
					ABountyDashParticle* BountyDashParticle = World->SpawnActor<ABountyDashParticle>(WhatToSpawn, Location, Rotation, SpawnParams);
					if (BountyDashParticle)
					{
						BountyDashParticle->SetKillPoint(GetKillPoint());
					}
				}
			}

			BountyDashCharacter->ScoreUp();
			GetWorld()->DestroyActor(this);
		}
	}
}
