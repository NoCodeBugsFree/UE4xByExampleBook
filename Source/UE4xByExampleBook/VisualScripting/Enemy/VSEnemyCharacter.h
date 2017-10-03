// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VSEnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	ES_Patrol UMETA(DisplayName = "Patrol"),
	ES_Wander UMETA(DisplayName = "Wander")
};

UCLASS()
class UE4XBYEXAMPLEBOOK_API AVSEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn Sensing Component  */
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComponent;

	/** Sphere component at left paw to inflict damage to player  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* LeftHandDamageTrigger;

	/** Sphere component at right paw to inflict damage to player  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* RightHandDamageTrigger;

	/** Health bar reference  */
	UPROPERTY()
	class UMyUserWidget* HealthBarWidget;

public:

	/** sets the health bar widget reference to update it when takes damage  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetHealthBarWidget(class UMyUserWidget* HealthBarWidgetToSet);

	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

protected:

	// Sets default values for this character's properties
	AVSEnemyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	
	/** Apply damage to this actor. */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	/** Event when this actor bumps into a blocking object, or blocks another actor that bumps into it. */
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
private:

	/** calls when hand trigger sphere was overlapped to inflict damage to character  */
	UFUNCTION()
	void OnHandTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	/** simple change body and eye color according to health  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ChangeColor();
	
	/** save character reference to blackboard  */
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	/* Hearing function - will be executed when we hear a Pawn */
	UFUNCTION()
	void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	/** calls when enemy takes damage to update health bar  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void UpdateHealthBarWidget();
	

	/** patrol points for this AI Character  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> PatrolPoints;
	
	// ------------- Blackboard names ---------------------------------------------
	/**
	 * use the same names in blackboard to correct work of OnSeeEnemy and OnHearNoise
	 *
	 *			AVSEnemyCharacter vars								       Blackboard
	 *
	 *														           Type	         Blackboard Name
	 *
	 *    FName PlayerName = "Player"	-------------------------  Object(Actor)    "Player"
	 *    FName LocationOfSoundName = "LocationOfSound";  -------  Vector           "LocationOfSound"
	 *    FName HasHeardSoundName = "HasHeardSound" -------------  bool             "HasHeardSound"
	 *
	 */ 


	/** same name as blackboard "Player" name  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackboard Variables Names", meta = (AllowPrivateAccess = "true"))
	FName PlayerName = "Player";
	
	/** same name as blackboard "LocationOfSound" name    */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackboard Variables Names", meta = (AllowPrivateAccess = "true"))
	FName LocationOfSoundName = "LocationOfSound";

	/** same name as blackboard "HasHeardSound" name    */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackboard Variables Names", meta = (AllowPrivateAccess = "true"))
	FName HasHeardSoundName = "HasHeardSound";

	// ------------- Blackboard names end ---------------------------------------------



	/** enemy health amount  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float EnemyHealth = 100.f;

	/** current state of the enemy  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EEnemyState EnemyState = EEnemyState::ES_Patrol;

	/**  shows whether we need to play attack anim or not */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsAttacking : 1;

	/** shows whether we need to play dead anim or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsDead : 1;

	/** shows whether we need to play dead anim or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 AttackingIndex = 0;

	/** attack damage per hit  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float AttackDamage = 33.f;
	
	/** after death enemy will be   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float RemoveFromLevelTime = 20.f;

public:

	/** calls to change AnimBP state from attacking state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void StopAttackAnimation();
	
	/** returns random Patrol Point from PatrolPoints array
	 *  no const because if we haven't any patrol points
	 *  we change the "EnemyState" of enemy to "ES_Wander"
	 */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	AActor* GetRandomPatrolPoint();

	/** sets the new state of the enemy */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetEnemyState(EEnemyState NewState) { EnemyState = NewState; }

	/** returns current enemy state */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	EEnemyState GetEnemyState() const { return EnemyState; }

	/** returns current enemy attacking flag state */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	bool IsAttacking() const { return bIsAttacking; }

	/** enables/disables hand damage triggers */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetCanAttack(bool bCanAttack);

	/** Perform attack  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Attack();
	
	/** returns current enemy dead flag state */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	bool IsDead() const { return bIsDead; }

	/** returns AttackingIndex */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetAttackingIndex() const { return AttackingIndex; }
		
};
