// Fill out your copyright notice in the Description page of Project Settings.

#include "BearStopAttackAnimNotify.h"
#include "BearAnimInstance.h"
#include "EnemyCharacter.h"

void UBearStopAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (UBearAnimInstance* BearAnimInstance = Cast<UBearAnimInstance>(MeshComp->GetAnimInstance()))
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(BearAnimInstance->GetOwningActor()))
		{
			EnemyCharacter->SetIsAttacking(false);
		}
	}
}
