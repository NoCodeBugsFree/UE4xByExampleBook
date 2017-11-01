// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	/** Perform attack  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnPerformAttack();

	/** Applied before performing an attack  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnPreAttack();

	/**  Perform attack done  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnPostAttack();

protected:

	// Sets default values for this character's properties
	AEnemyCharacter();

	/**  Allow actors to initialize themselves on the C++ side */
	void PostInitializeComponents() override;
	
private:
	
	/** calls when hand trigger sphere was overlapped to inflict damage to character  */
	UFUNCTION()
	void OnHandTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/** Hear the player's noise using the sensing component  */
	UFUNCTION()
	void OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume);

	/** See the player's by sight using the sensing component  */
	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);

	/** enables/disables overlap event on attacking capsules */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetCanAttack(bool bCanAttack);


	// -----------------------------------------------------------------------------------

	/** Sphere component around Enemy body to accumulate damage  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* BodySphereTrigger;

	/** Sphere component at left paw to inflict damage to player  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* LeftHandDamageTrigger;

	/** Sphere component at right paw to inflict damage to player  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* RightHandDamageTrigger;

	/** Pawn Sensing Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* PawnSensor;

	/** The health of the enemy  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float TotalHealth = 100.f;

	/**  The range for the enemy attack */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 100.f;
	
	/** per attack damage  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float AttackDamage = 20.f;

	/** shows whether enemy character is dead on not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	/** shows whether enemy character is attacking now or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking = false;

	/** represents index for different animations per attack  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 AttackingIndex = 0;

public:	

	/** change bIsAttacking to new state */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetIsAttacking(bool NewIsAttacking) { bIsAttacking = NewIsAttacking; }
	
	/** returns BodySphereTrigger subobject **/
	FORCEINLINE class USphereComponent* GetBodySphereTrigger() const { return BodySphereTrigger; }

	/** returns bIsAttacking **/
	FORCEINLINE bool GetIsAttacking() const { return bIsAttacking; }

	/** returns bIsDead **/
	FORCEINLINE bool GetIsDead() const { return bIsDead; }

	/** returns AttackingIndex **/
	FORCEINLINE int32 GetAttackingIndex() const { return AttackingIndex; }
	
};
