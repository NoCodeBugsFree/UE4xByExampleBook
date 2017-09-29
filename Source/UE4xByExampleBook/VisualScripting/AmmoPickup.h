// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AAmmoPickup : public AStaticMeshActor
{
	GENERATED_BODY()
	
protected:

	AAmmoPickup();

	virtual void PostInitializeComponents() override;

private:

	/** Sound to play each time ammo was collected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USoundBase* CollectSound;

	/* Capsule Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	
	/* Amount of ammo to add  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 AmmoToAdd = 10;

	// -----------------------------------------------------------------------------------

	/** calls for handling overlap event  */
	UFUNCTION()
	void OnOverlap(AActor* OverlapedActor, AActor* OtherActor);
	
};
