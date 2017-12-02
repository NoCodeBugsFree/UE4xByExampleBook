// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AInventoryActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4XBYEXAMPLEBOOK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<AInventoryActor*> CurrentInventory;

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 AddToInventory(AInventoryActor* ActorToAdd);

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void RemoveFromInventory(AInventoryActor* ActorToRemove);

protected:

	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:	
	
		
	
};
