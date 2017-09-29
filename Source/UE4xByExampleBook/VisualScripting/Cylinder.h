// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Cylinder.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ACylinder : public AStaticMeshActor
{
	GENERATED_BODY()
	
private:

	ACylinder();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/**
	* Event when this actor bumps into a blocking object, or blocks another actor that bumps into it.
	* This could happen due to things like Character movement, using Set Location with 'sweep' enabled, or physics simulation.
	* For events when objects overlap (e.g. walking into a trigger) see the 'Overlap' event.
	*
	* @note For collisions during physics simulation to generate hit events, 'Simulation Generates Hit Events' must be enabled.
	* @note When receiving a hit from another object's movement (bSelfMoved is false), the directions of 'Hit.Normal' and 'Hit.ImpactNormal'
	* will be adjusted to indicate force from the other object against this object.
	*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	/** calls to reverse movement direction  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ReverseDirection();

	// -----------------------------------------------------------------------------------

	/** movement speed  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Speed = 200.f;

	/** shows whether this actor is primed or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsPrimed = false;

	/** reverse movement direction delay  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float ReverseDelay = 3.f;

	/** movement direction  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FVector Direction = FVector(0.f, -10.f, 0.f);

	/** Material to set when hit  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* HitMaterial;

	/** sound to play when explode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USoundBase* ExplosionSound;

	/* explosion emitter template */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ExplosionEmitterTemplate;
	
};
