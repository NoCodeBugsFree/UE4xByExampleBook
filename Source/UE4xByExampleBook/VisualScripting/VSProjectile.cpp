// Fill out your copyright notice in the Description page of Project Settings.

#include "VSProjectile.h"
#include "Components/SphereComponent.h"

// Sets default values
AVSProjectile::AVSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereCollider);
	SphereCollider->SetSphereRadius(55.f);

	SphereCollider->SetCollisionProfileName("BlockAll");

	ProjectileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileStaticMesh"));
	ProjectileStaticMesh->SetupAttachment(RootComponent);
	ProjectileStaticMesh->SetCollisionProfileName("NoCollision");

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 6000.f;
	ProjectileMovementComponent->MaxSpeed = 6000.f;
	ProjectileMovementComponent->bShouldBounce = true;

	InitialLifeSpan = 5.f;
}
