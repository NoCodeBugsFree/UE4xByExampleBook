// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasteringUE4x/PickupBase.h"
#include "CoinPickup.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ACoinPickup : public APickupBase
{
	GENERATED_BODY()
	
public:

	/** returns the amount of coins  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetCoinValue() const { return CoinValue; }

	/** calls when this pickup was collected  */
	virtual void OnGetCollected_Implementation(AActor* OtherActor) override;

protected:
	
	/** The value that the coin adds to the collected items, you can make a Special coins with higher values or so...  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (BlueprintProtected = "true"))
	float CoinValue = 20.f;
	
};
