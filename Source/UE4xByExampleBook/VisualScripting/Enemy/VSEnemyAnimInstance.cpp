// Fill out your copyright notice in the Description page of Project Settings.

#include "VSEnemyAnimInstance.h"
#include "VSEnemyCharacter.h"

UVSEnemyAnimInstance::UVSEnemyAnimInstance()
{
	bIsAttacking = false;
	bIsDead = false;
}

void UVSEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (AVSEnemyCharacter* VSEnemyCharacter = Cast<AVSEnemyCharacter>(TryGetPawnOwner()))
	{
		/** dead  */
		bIsDead = VSEnemyCharacter->IsDead();

		/** attacking   */
		bIsAttacking = VSEnemyCharacter->IsAttacking();

		/** speed  */
		Speed = VSEnemyCharacter->GetVelocity().Size();

		/** index  */
		AttackingIndex = VSEnemyCharacter->GetAttackingIndex();
	}
}
