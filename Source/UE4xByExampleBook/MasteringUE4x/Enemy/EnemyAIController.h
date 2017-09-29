// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AEnemyAIController();

	/** Transient Property is transient: shouldn't be saved, zero-filled at load time.  */
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;

	/** returns the enemy reference  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	class AGladiator* GetEnemy() const;

	/** attempt to find an enemy  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnSearchForEnemy();

protected:

	/**
	* Handles attaching this controller to the specified pawn.
	* Only runs on the network authority (where HasAuthority() returns true).
	* @param InPawn The Pawn to be possessed.
	* @see HasAuthority()
	*/
	virtual void Possess(APawn* InPawn) override;

	/** calls in posses to initialize blackboard and start behavior tree  */
	void InitBlackBoardandStartBehaviorTree(APawn* InPawn);

	/** State entered when inactive (no possessed pawn, not spectating, etc). */
	virtual void BeginInactiveState() override;

	/** sets the enemy reference  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetEnemy(APawn* InPawn);
	
	/**  responsible for updating the rotation of the controller to the walking direction (usually forward). */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void UpdateControllerRotation(float DeltaTime, bool bUpdatePawn);

	/**   tell whether the AI can see its enemy (the player) or can't see it. */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	bool PawnCanBeSeen(APawn* Target);
	
	int32 EnemyKeyID;

	int32 EnemyPositionKeyID;

private:
	
	
};
