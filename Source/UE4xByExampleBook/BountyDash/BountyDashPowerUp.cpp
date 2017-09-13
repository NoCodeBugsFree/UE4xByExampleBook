// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashPowerUp.h"
#include "PowerUpObject.h"
#include "Obstacle.h"
#include "BountyDashCharacter.h"
#include "Components/SphereComponent.h"

ABountyDashPowerUp::ABountyDashPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

	PowerUp = CreateDefaultSubobject<UPowerUpObject>(TEXT("PowerUp"));
	check(PowerUp);
	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(PowerUpMesh);
	PowerUpMesh->SetupAttachment(RootComponent);
	PowerUpMesh->SetCollisionProfileName("OverlapAllDynamic");
	
}

void ABountyDashPowerUp::MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	/**  same obstacle collision check   */
	if (OtherActor && OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()))
	{
		USphereComponent* OtherSphere = Cast<USphereComponent>(OtherActor->GetComponentByClass(USphereComponent::StaticClass()));
		if (OtherSphere)
		{
			AddActorLocalOffset(FVector(0.0f, 0.0f, (OtherSphere->GetUnscaledSphereRadius()) + Collider->GetUnscaledSphereRadius() * 2));
		}
	}

	/** Character colliding test  */
	if (OtherActor && OtherActor->GetClass()->IsChildOf(ABountyDashCharacter::StaticClass()) && !IsPendingKill())
	{
		ABountyDashCharacter* BountyDashCharacter = Cast<ABountyDashCharacter>(OtherActor);
		if (BountyDashCharacter)
		{
			BountyDashCharacter->PowerUp(PowerUpType);
			
			// Books way
			// BountyDashCharacter->PowerUp(PowerUp->GetType());

			Destroy();
		}
	}
}
