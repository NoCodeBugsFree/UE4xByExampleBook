// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ASimpleCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCameraComponent;

	/**  Inventory Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* MyInventory;

public:
	
	
protected:

	// Sets default values for this character's properties
	ASimpleCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
		
	// -----------------------------------------------------------------------------------

	/** Handles forwards and backwards movement  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void MoveForward(float Value);

	/**  Handles left and right strafing movement  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void MoveRight(float Value);

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void DropItem();

	/**   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void TakeItem(class AInventoryActor* InventoryItem);
	
public:	
	
	
	
};
