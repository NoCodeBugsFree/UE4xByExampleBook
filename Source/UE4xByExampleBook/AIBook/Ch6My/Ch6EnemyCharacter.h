// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ch6EnemyCharacter.generated.h"



UCLASS()
class UE4XBYEXAMPLEBOOK_API ACh6EnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn Sensing Component  */
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComponent;

	/** Calls every time when this character see the player  */
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);
	
	/* Hearing function - will be executed when we hear a Pawn */
	UFUNCTION()
	void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

public:

	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	/** calls to set current PP  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetCurrentPatrolPoint(class ACh6TargetPoint* NewTargetPoint);
	
protected:

	// Sets default values for this character's properties
	ACh6EnemyCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

private:

	/** Current Patrol Point  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ACh6TargetPoint* CurrentPatrolPoint;

public:

	/** returns current PP **/
	FORCEINLINE class ACh6TargetPoint* GetCurrentPatrolPoint() const { return CurrentPatrolPoint; }
	

};
