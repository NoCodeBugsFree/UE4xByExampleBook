// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BossAIController.generated.h"

/**
 * 
 */

/** Boss State according to health value  */
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
	
	
	/** Sets the bIsTracking flag according to BB data  */
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void TrackToTarget();

	/** Sets the bIsTracking flag to false and nullify the Enemy reference  */
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void StopTrack();
	
	/** Find Launch points near possessed character and attempts to spawn required amount of missiles  */
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

	// -----------------------------------------------------------------------------------

	/** Boss State Blackboard Key  */
	FBlackboard::FKey BossStateBlackboardKey;
	
	/** Target Blackboard Key  */
	FBlackboard::FKey TargetBlackboardKey;
	
	// -----------------------------------------------------------------------------------

	/** Current Boss State  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EBossState BossState = EBossState::BS_FOLLOW;
	
	/** Enemy reference  */
	class ABossModeCharacter* Target;

	/** Flag that shows whether this AI is tacking the enemy or not  */
	bool bIsTracking;


	/** Sets the boss state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetBossState(EBossState NewEBossState) { BossState = NewEBossState; }
	
public:

	/** Calls every time when Boss takes damage, calls the SetBossState to accommodate current boss state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetStateAccordingCurrentHealth();

	/** Returns BlackboardComponent **/
	FORCEINLINE class UBlackboardComponent* GetBlackboard() const { return BlackboardComponent; }

};
