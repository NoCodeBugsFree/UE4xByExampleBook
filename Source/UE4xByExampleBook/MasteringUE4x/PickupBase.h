// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	/** The pickup active or not!  */
	UFUNCTION(BlueprintPure, Category = "Pickups")
	bool IsActive() const { return bIsActive; }

	/**  Change the active status from the outside */
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void SetActive(bool NewPickupState) { bIsActive = NewPickupState; }

	/** calls when this pickup was collected  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void OnGetCollected(AActor* OtherActor);
	virtual void OnGetCollected_Implementation(AActor* OtherActor);

protected:

	// Sets default values for this actor's properties
	APickupBase();
	
private:
	
	/* Pickup static mesh  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
	
	/* Sphere Collider */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;
	
	/** shows whether this pickup is active or not. Active by default  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsActive = true;

public:	
	
	/** retunrs Pickup Static Mesh Component **/
	FORCEINLINE class UStaticMeshComponent* GetStaticMeshComponent() const { return PickupMesh; }
	
};
