// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeOfDayHandler.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTimeChangedSignature, int32, int32)

UCLASS()
class UE4XBYEXAMPLEBOOK_API ATimeOfDayHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	
	FOnTimeChangedSignature OnTimeChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 TimeScale = 60;
	
	int32 Hours = 0;
	
	int32 Minutes = 0;

	float ElapsedSeconds = 0;

protected:

	// Sets default values for this actor's properties
	ATimeOfDayHandler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	
};
