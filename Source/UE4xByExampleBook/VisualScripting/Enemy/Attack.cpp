// Fill out your copyright notice in the Description page of Project Settings.

#include "Attack.h"
#include "VSEnemyCharacter.h"

UAttack::UAttack()
{
	bEnableAttack = true;
}

void UAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		if(AVSEnemyCharacter* VSEnemyCharacter = Cast<AVSEnemyCharacter>(MeshComp->GetOwner()))
		{
			/** enables/disables enemy attack state  */
			VSEnemyCharacter->SetCanAttack(bEnableAttack);
		}
	}
}
