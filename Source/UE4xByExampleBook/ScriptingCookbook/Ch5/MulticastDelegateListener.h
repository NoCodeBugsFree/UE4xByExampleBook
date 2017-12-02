// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MulticastDelegateListener.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AMulticastDelegateListener : public AActor
{
	GENERATED_BODY()
	
	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* PointLightComponent;

public:	
	// Sets default values for this actor's properties
	AMulticastDelegateListener();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ToggleLight();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
