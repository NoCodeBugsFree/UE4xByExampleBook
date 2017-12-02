// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GravityObject.h"
#include "PhysicsCube.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API APhysicsCube : public AActor, public IGravityObject
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MyMesh;

public:	
	// Sets default values for this actor's properties
	APhysicsCube();

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return MyMesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
