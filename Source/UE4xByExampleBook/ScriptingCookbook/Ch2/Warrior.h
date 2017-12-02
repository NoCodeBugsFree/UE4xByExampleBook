// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Warrior.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AWarrior : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarrior();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	FString Name;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	FString ToString();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
