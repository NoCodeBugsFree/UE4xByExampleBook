// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BountyDashObject.h"
#include "Obstacle.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AObstacle : public ABountyDashObject
{
	GENERATED_BODY()
	
	

protected:

	// Sets default values for this actor's properties
	AObstacle();

	UFUNCTION()
	virtual void MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	virtual void MyOnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
public:	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
	class UDestructibleComponent* Mesh;

	UDestructibleComponent* GetDestructable();
	
};
