// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTriggerVolume.generated.h"

/** declare  */
DECLARE_EVENT(AMyTriggerVolume, FPlayerEntered)

UCLASS()
class UE4XBYEXAMPLEBOOK_API AMyTriggerVolume : public AActor
{
	GENERATED_BODY()
	
	/* Trigger Zone  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerZone;

public:	
	
	FPlayerEntered OnPlayerEntered;

protected:

	// Sets default values for this actor's properties
	AMyTriggerVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
public:	
	
	
	
};
