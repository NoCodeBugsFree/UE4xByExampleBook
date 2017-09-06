// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BossCharacter.h"

// Sets default values
ABossModeProjectile::ABossModeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	ProjCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	ProjCollision->InitSphereRadius(10.0f);
	ProjCollision->BodyInstance.SetCollisionProfileName("BlockAll");
	ProjCollision->OnComponentHit.AddDynamic(this, &ABossModeProjectile::OnHit);
	ProjCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	ProjCollision->CanCharacterStepUpOn = ECB_No;
	SetRootComponent(ProjCollision);

	OnDestroyed.AddDynamic(this, &ABossModeProjectile::OnDestoyedProjectile);

	ProjMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComp"));
	ProjMesh->SetupAttachment(ProjCollision);
	ProjMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ProjParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ProjParticle->bAutoActivate = false;
	ProjParticle->SetupAttachment(ProjCollision);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjMovement->UpdatedComponent = ProjCollision;
	ProjMovement->InitialSpeed = 3000.f;
	ProjMovement->MaxSpeed = 3000.f;
	ProjMovement->bRotationFollowsVelocity = true;

	ProjMovement->bIsHomingProjectile = true;
	ProjMovement->HomingAccelerationMagnitude = 10000.f;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABossModeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossModeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossModeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->GetClass()->IsChildOf(ABossCharacter::StaticClass()))
	{
		FDamageEvent DamageEvent(UDamageType::StaticClass());
		OtherActor->TakeDamage(10.0f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
	}

	if(OtherActor && !OtherActor->GetClass()->IsChildOf(this->StaticClass()))
	{
		ProjCollision->SetCollisionProfileName(TEXT("NoCollision"));
		ProjCollision->bGenerateOverlapEvents = false;
		ProjMesh->SetVisibility(false);
		ProjParticle->Activate();
		ProjParticle->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}
}

void ABossModeProjectile::OnDestoyedProjectile(AActor * OtherActor)
{

}

