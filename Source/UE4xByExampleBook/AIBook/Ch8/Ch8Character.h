// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ch8Character.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ACh8Character : public ACharacter
{
	GENERATED_BODY()

	/** Text Render Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* CharText;

	/* SpringArmComponent  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	
	/* Camera Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	
public:

	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	/** Apply damage to this actor. */
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	
	// Sets default values for this character's properties
	ACh8Character();

	void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	void Tick(float DeltaTime) override;

private:

	/** sets the text render component text according to character's health amount  */
	void SetHealthText() const;

	/** the amount of health for this character  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Health = 100.f;

};
