// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wearable.h"
#include "Boots.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABoots : public AActor, public IWearable
{
	GENERATED_BODY()
	
public:	
	
	//~ Begin IWearable Interface
	int32 GetStrengthRequirement_Implementation() override;

	bool CanEquip_Implementation(APawn* Wearer) override;

	void OnEquip_Implementation(APawn* Wearer) override;
	//~ End IWearable Interface

protected:

	// Sets default values for this actor's properties
	ABoots();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	


	
	
};
