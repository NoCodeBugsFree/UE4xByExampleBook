// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BearAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UBearAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:	
		
	/** Native update override point. It is usually a good idea to simply gather data in this step and
		for the bulk of the work to be done in NativeUpdateAnimation.  */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/** Attacking animation number allows different animations each attack  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 AttackingIndex = 0;

	/** shows whether bear should play attacking animations or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking = false;

	/**  shows whether bear should play death animations or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;
	
	/** bears current movement speed to animate  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float BearMovementSpeed = 0.f;
	
	
};
