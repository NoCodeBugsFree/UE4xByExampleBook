// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ch6AIController.generated.h"

/**
 * 
 */

/** represents AI state  */
UENUM(BlueprintType)
enum class ECh6EnemyState : uint8
{
	ECh6_Patrol			UMETA(DisplayName = "Patrol"),
	ECh6_Dead			UMETA(DisplayName = "Dead"),
	ECh6_Attack			UMETA(DisplayName = "Attack"),
	ECh6_Wander			UMETA(DisplayName = "Wander"),
	ECh6_Suspicious		UMETA(DisplayName = "Suspicious")
};

UCLASS()
class UE4XBYEXAMPLEBOOK_API ACh6AIController : public AAIController
{
	GENERATED_BODY()
	
private:

	ACh6AIController();

	void Possess(APawn* Pawn) override;

	/** Blackboard Component  */
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent;
	
	/** BehaviorTree Component  */
	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	
	/** current AI state  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"), BlueprintSetter = SetState)
	ECh6EnemyState State = ECh6EnemyState::ECh6_Patrol;
	
public:

	/** returns BB comp  **/
	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }

	/** returns current AI state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	ECh6EnemyState GetState() const { return State; }

	/** calls to set new AI state  */
	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "AAA")
	void SetState(ECh6EnemyState NewState);

};
