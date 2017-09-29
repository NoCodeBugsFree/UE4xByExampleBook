// Fill out your copyright notice in the Description page of Project Settings.

#include "EnableBearAttackAnimNotify.h"
#include "BearAnimInstance.h"
#include "EnemyCharacter.h"


void UEnableBearAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (UBearAnimInstance* BearAnimInstance = Cast<UBearAnimInstance>(MeshComp->GetAnimInstance()))
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(BearAnimInstance->GetOwningActor()))
		{
			/** activates left and right attacking spheres to enable attacking  */
			EnemyCharacter->OnPreAttack();
		}
	}
}
