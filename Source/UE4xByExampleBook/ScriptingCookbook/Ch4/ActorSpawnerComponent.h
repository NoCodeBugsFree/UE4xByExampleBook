// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ActorSpawnerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4XBYEXAMPLEBOOK_API UActorSpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	

protected:

	// Sets default values for this component's properties
	UActorSpawnerComponent();
	
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Spawn();
	
	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;

public:	
	
		
	
};
