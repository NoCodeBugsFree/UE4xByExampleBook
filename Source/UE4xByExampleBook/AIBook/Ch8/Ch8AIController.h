// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ch8AIController.generated.h"

UENUM(BlueprintType)
enum class ECh8EnemyAiState : uint8
{
	AS_Patrol UMETA(DisplayName = "Patrol"),
	AS_Wander UMETA(DisplayName = "Wander")
};


/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ACh8AIController : public AAIController
{
	GENERATED_BODY()
	
	/** AI Perception Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* AIPerceptionComponent;
	
public:
	
	/**  calls to hook OnPerceptionUpdate event */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnUpdatePerception(TArray<AActor*> UpdatedActors);

	/**  gets random target point */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	class ACh8TargetPoint* GetRandomTargetPoint() const;

	/** retunrs blackboard comp **/
	FORCEINLINE class UBlackboardComponent* GetBlackboardComp() const { return BlackboardComponent; }
	
	void SetAiState(ECh8EnemyAiState NewState);

	ECh8EnemyAiState GetAiState() const { return AiState; }

protected:

	void Possess(APawn* Pawn) override;

	ACh8AIController();

	void OnConstruction(const FTransform& Transform) override;

	void BeginPlay() override;

	/** Blackboard Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;

	/** BehaviorTree Component  */
	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorTreeComponent;

private:

	/** Ai State Name in blackboard */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FName AiStateName = "State";

	/** current state of AI  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	ECh8EnemyAiState AiState = ECh8EnemyAiState::AS_Patrol;

	/** all patrol points for this AI to patrol  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class ACh8TargetPoint*> TargetPoints;
	
};
