// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectableCube.h"

ASelectableCube::ASelectableCube()
{
	GetMesh()->SetNotifyRigidBodyCollision(true);
}

void ASelectableCube::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (IsCubeSelectable())
	{
		TrySelect();
	}
}
