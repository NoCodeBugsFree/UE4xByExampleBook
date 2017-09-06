// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossModeProjectile.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABossModeProjectile : public AActor
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* ProjCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ProjParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ProjMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjMovement;

public:	
	

protected:

	// Sets default values for this actor's properties
	ABossModeProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// On Component Hit
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnDestoyedProjectile(AActor * OtherActor);

public:	
	
	/** Returns Projectile Movement Component  */
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjMovement; }

	/** Returns Projectile Sphere Collision Component  */
	FORCEINLINE class USphereComponent* GetSphereComponent() const { return ProjCollision; }
	
};
