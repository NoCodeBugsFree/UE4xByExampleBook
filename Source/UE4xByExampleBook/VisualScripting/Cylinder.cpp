// Fill out your copyright notice in the Description page of Project Settings.

#include "Cylinder.h"
#include "VSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "VSCharacter.h"

ACylinder::ACylinder()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetCollisionProfileName("BlockAllDynamic");
}

void ACylinder::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle ReverseDirectionTimer;
	GetWorldTimerManager().SetTimer(ReverseDirectionTimer, this, &ACylinder::ReverseDirection, ReverseDelay, true);
}

void ACylinder::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Direction.Normalize(1.f);

	FVector LocationNextFrame = Direction * Speed * DeltaSeconds;

	SetActorLocation(LocationNextFrame + GetActorLocation());
}

void ACylinder::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	
	/** 1st hit - change material and return */
	if (Other && Other != this && !IsPendingKill() && HitMaterial && !bIsPrimed)
	{
		/** can be hit only by projectile  */
		AVSProjectile* VSProjectile = Cast<AVSProjectile>(Other);
		if (VSProjectile && !VSProjectile->IsPendingKill())
		{
			if (HitMaterial)
			{
				GetStaticMeshComponent()->SetMaterial(0, HitMaterial);
			}
			bIsPrimed = true;
			return;
		}
	}

	/** 2ns hit - play FX and destroy  */
	if (bIsPrimed)
	{
		/**  play explosion sound */
		if (ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
		}

		/** spawn explosion particles  */
		if (ExplosionEmitterTemplate)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEmitterTemplate, GetActorTransform());
		}

		/** if we still hit by projectile  */
		if (AVSProjectile* VSProjectile = Cast<AVSProjectile>(Other))
		{
			/** retrieve a Killer reference  */
			if (AVSCharacter* OurKiller = Cast<AVSCharacter>(VSProjectile->GetOwner()))
			{
				/** add ourself to killed targets  */
				OurKiller->AddTargetKilled();
			}
		}

		Destroy();
	}
}

void ACylinder::ReverseDirection()
{
	Direction = -Direction;
}
