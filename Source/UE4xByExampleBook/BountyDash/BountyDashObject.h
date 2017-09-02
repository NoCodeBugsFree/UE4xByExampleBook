// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BountyDashObject.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABountyDashObject : public AActor
{
	GENERATED_BODY()
	
public:	
	
	void SetKillPoint(float point);

	float GetKillPoint();

protected:

	// Sets default values for this actor's properties
	ABountyDashObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	virtual void MyOnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Collider;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ABountyDashGameMode* BountyDashGameMode;
	
	float KillPoint = -20000.0f;

};
