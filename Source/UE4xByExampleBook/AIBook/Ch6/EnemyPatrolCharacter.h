// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyPatrolCharacter.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	AS_Patrol	UMETA(DisplayName = "Patrol"),
	AS_Dead		UMETA(DisplayName = "Dead"),
	AS_Attack	UMETA(DisplayName = "Attack")
};

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerceptionUpdatedDelegate, TArray<AActor*>, UpdatedActors);

UCLASS()
class UE4XBYEXAMPLEBOOK_API AEnemyPatrolCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** AI Perception Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* AIPerceptionComponent;

public:

	/** calls to change the AI state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetState(EAIState NewState) { State = NewState; }

	/** returns current AI state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	EAIState GetState() const { return State; }

protected:

	// Sets default values for this character's properties
	AEnemyPatrolCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	/**   */
	UFUNCTION()
	void OnUpdatePerception(TArray<AActor*> UpdatedActors);

	/** This will maintain our current state within our state machine  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EAIState State = EAIState::AS_Patrol;

};
