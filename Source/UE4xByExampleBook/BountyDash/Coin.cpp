// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "BountyDashCharacter.h"
#include "BountyDashGameMode.h"
#include "Components/SphereComponent.h"
#include "Obstacle.h"
#include "BountyDashParticle.h"

ACoin::ACoin()
{
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(CoinMesh);
	CoinMesh->SetupAttachment(RootComponent);
	CoinMesh->SetCollisionProfileName("OverlapAllDynamic");
}

void ACoin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	/** WTF is URotatingMovementComponent ??? */
	CoinMesh->AddLocalRotation(FRotator(0.0f, 5.0f, 0.0f));
}

void ACoin::MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	/** We need to detect if the coin is currently colliding with an obstacle. 
	    If so, we need to adjust the height of the coin object 
	 */
	LiftCollidingCoin(OtherActor);

	/** if we collide with Bounty Dash Character  */
	CollideWithCharacter(OtherActor);
}

void ACoin::CollideWithCharacter(AActor* OtherActor)
{
	if (OtherActor && OtherActor->GetClass()->IsChildOf(ABountyDashCharacter::StaticClass()) && !IsPendingKill())
	{
		ABountyDashCharacter* BountyDashCharacter = Cast<ABountyDashCharacter>(OtherActor);
		if (BountyDashCharacter)
		{
			if (BountyDashParticlesToSpawn)
			{
				UWorld* const World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = Instigator;

					FVector Location = BountyDashCharacter->GetActorLocation();
					FRotator Rotation = FRotator::ZeroRotator;

					ABountyDashParticle* BountyDashParticle = World->SpawnActor<ABountyDashParticle>(BountyDashParticlesToSpawn, Location, Rotation, SpawnParams);
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

void ACoin::LiftCollidingCoin(AActor* OtherActor)
{
	if (OtherActor && OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()) && !bIsBeingPulled)
	{	
		USphereComponent* OtherSphere = Cast<USphereComponent>(OtherActor->GetComponentByClass(USphereComponent::StaticClass()));
		if (OtherSphere  && Collider)
		{
			/** lift this coin to according height  */
			AddActorLocalOffset(FVector(0.0f, 0.0f, (OtherSphere->GetUnscaledSphereRadius() * 2.0f) + Collider->GetUnscaledSphereRadius()));
		}
	}
}
