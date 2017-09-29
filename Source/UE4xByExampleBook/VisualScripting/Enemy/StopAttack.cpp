// Fill out your copyright notice in the Description page of Project Settings.

#include "StopAttack.h"
#include "VSEnemyCharacter.h"

void UStopAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		if (AVSEnemyCharacter* VSEnemyCharacter = Cast<AVSEnemyCharacter>(MeshComp->GetOwner()))
		{
			VSEnemyCharacter->StopAttackAnimation();
		}
	}
}
