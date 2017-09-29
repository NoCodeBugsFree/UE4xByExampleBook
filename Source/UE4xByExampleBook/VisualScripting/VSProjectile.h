// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VSProjectile.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AVSProjectile : public AActor
{
	GENERATED_BODY()
	
	/* represents projectile static mesh  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ProjectileStaticMesh;

	/*   represents sphere collider */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollider;

	/* Projectile Movement Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

protected:

	// Sets default values for this actor's properties
	AVSProjectile();

private:

	/** amount of damage to cause  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float DamageToCause = 33.f;
	
public:

	/** returns DamageToCause value  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetDamageToCause() const { return DamageToCause; }
	
};
