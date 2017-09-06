// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BossAIController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBossState : uint8
{
	BS_FOLLOW = 0 UMETA(DisplayName = "Follow"),
	BS_TURRET = 1 UMETA(DisplayName = "Turret"),
	BS_FINAL  = 2 UMETA(DisplayName = "Final")
};


class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABossAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABossAIController();

	virtual void Possess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UBlackboardComponent* GetBlackboard() const { return BlackboardComponent; }

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void TrackToTarget();

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void StopTrack();
	
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void FireMissles();
	
private:
	
	/** Blackboard Component  */
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent;
	
	/** BehaviorTree Component  */
	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	/** Controlled AI Character Reference  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class ABossCharacter* ControlledCharacter;

	FBlackboard::FKey BossStateBlackboardKey;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EBossState BossState = EBossState::BS_FOLLOW;

	FBlackboard::FKey TargetBlackboardKey;

	class ABossModeCharacter* Target;

	bool bIsTracking;

};
