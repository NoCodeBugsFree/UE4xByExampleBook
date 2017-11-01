// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VSEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UVSEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	UVSEnemyAnimInstance();

	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeUpdateAnimation.
	void NativeUpdateAnimation(float DeltaSeconds) override;
	
	/**  shows whether we need to play attack anim or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsAttacking : 1;

	/**  shows whether we need to play attack anim or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 AttackingIndex = 0;
	
	/** shows whether we need to play dead anim or not  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsDead : 1;

	/** enemies movement speed  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Speed;
};
