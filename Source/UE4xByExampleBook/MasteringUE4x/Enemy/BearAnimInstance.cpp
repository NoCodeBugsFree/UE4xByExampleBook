// Fill out your copyright notice in the Description page of Project Settings.

#include "BearAnimInstance.h"
#include "MasteringUE4x/Enemy/EnemyCharacter.h"

void UBearAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* TestPawn = TryGetPawnOwner();
	if (TestPawn)
	{	
		if (AEnemyCharacter* BearCharacter = Cast<AEnemyCharacter>(TestPawn))
		{
			AttackingIndex = BearCharacter->GetAttackingIndex();

			BearMovementSpeed = BearCharacter->GetVelocity().Size();

			bIsAttacking = BearCharacter->GetIsAttacking();

			bIsDead = BearCharacter->GetIsDead();
		}
	}
}
	
