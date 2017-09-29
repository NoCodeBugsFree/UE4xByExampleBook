// Fill out your copyright notice in the Description page of Project Settings.

#include "DisableBearAttackAnimNotify.h"
#include "BearAnimInstance.h"
#include "EnemyCharacter.h"



void UDisableBearAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (UBearAnimInstance* BearAnimInstance = Cast<UBearAnimInstance>(MeshComp->GetAnimInstance()))
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(BearAnimInstance->GetOwningActor()))
		{
			/** deactivates left and right attacking spheres to disable attacking  */
			EnemyCharacter->OnPostAttack();
		}
	}
}
