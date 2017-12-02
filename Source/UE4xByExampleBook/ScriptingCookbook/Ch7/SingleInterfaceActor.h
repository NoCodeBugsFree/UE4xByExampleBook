// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "SingleInterfaceActor.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ASingleInterfaceActor : public AActor, public IMyInterface
{
	GENERATED_BODY()
	
public:	
	
	virtual FString GetTestName() const override;

protected:

	// Sets default values for this actor's properties
	ASingleInterfaceActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	

	
	
};
