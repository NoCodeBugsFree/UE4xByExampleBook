// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParamDelegateListener.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AParamDelegateListener : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* PointLightComponent;
	
public:	
	

protected:

	// Sets default values for this actor's properties
	AParamDelegateListener();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetLightColor(FLinearColor LightColor, bool bEnableLight);

public:	
	
	
	
};
