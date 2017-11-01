// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DogCharacter.generated.h"

UENUM(BlueprintType)
enum class EDogState : uint8
{
	DS_Hungry UMETA(DisplayName = "Hungry"),
	DS_Barking UMETA(DisplayName = "Barking"),
	DS_Idle UMETA(DisplayName = "Idle")
};

UCLASS()
class UE4XBYEXAMPLEBOOK_API ADogCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn Sensing Component  */
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComponent;

public:

	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	/** sets the DogState to new state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetDogState(EDogState NewDogState);
	
	/** returns Dog State  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	EDogState GetDogState() const { return DogState; }
	
protected:

	// Sets default values for this character's properties
	ADogCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;
	
private:
	
	/** Calls every time when this character see the player  */
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);
	
	/** calls to change dog state to another state  */
	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "AAA")
	void SetRandomDogState();

	/** frequency for changing dog state  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float ChangeDogStateTime = 5.f;

	/** Current Dog State  */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetDogState, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EDogState DogState = EDogState::DS_Idle;

public:

	/** returns Pawn Sensing Component  **/
	FORCEINLINE class UPawnSensingComponent* GetPawnSensingComponent() const { return PawnSensingComponent; }

};