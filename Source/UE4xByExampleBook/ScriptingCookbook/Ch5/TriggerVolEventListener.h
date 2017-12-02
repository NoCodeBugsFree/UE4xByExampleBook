// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerVolEventListener.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ATriggerVolEventListener : public AActor
{
	GENERATED_BODY()
	
	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* PointLightComponent;

public:	
	// Sets default values for this actor's properties
	ATriggerVolEventListener();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class AMyTriggerVolume* TriggerEventSource;

	/**   */
	UFUNCTION()
	void OnTriggerEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
