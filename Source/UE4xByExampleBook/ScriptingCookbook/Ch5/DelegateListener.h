// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateListener.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ADelegateListener : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ADelegateListener();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void EnableLight();

	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* PointLight;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
