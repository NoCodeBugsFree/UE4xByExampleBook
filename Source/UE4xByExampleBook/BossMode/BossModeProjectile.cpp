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
	PrimaryActorTick.bCanEverTick = false;
	
	// Use a sphere as a simple collision representation
	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	ProjectileCollision->InitSphereRadius(10.0f);
	ProjectileCollision->BodyInstance.SetCollisionProfileName("BlockAll");
	ProjectileCollision->OnComponentHit.AddDynamic(this, &ABossModeProjectile::OnHit);
	ProjectileCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	ProjectileCollision->CanCharacterStepUpOn = ECB_No;
	SetRootComponent(ProjectileCollision);
	
	OnDestroyed.AddDynamic(this, &ABossModeProjectile::OnDestoyedProjectile);

	/** Mesh  */
	ProjectileMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComp"));
	ProjectileMesh->SetupAttachment(ProjectileCollision);
	ProjectileMesh->SetCollisionProfileName(TEXT("NoCollision"));

	/** Particles  */
	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ProjectileParticle->bAutoActivate = false;
	ProjectileParticle->SetupAttachment(ProjectileCollision);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = ProjectileCollision;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = 50000.f;

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
		ProjectileCollision->SetCollisionProfileName(TEXT("NoCollision"));
		ProjectileCollision->bGenerateOverlapEvents = false;
		ProjectileMesh->SetVisibility(false);
		ProjectileParticle->Activate();
		ProjectileParticle->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}
}

void ABossModeProjectile::OnDestoyedProjectile(AActor* OtherActor)
{
	// =)
}

