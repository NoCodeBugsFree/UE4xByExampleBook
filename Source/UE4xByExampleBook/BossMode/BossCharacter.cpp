// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"


// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   /** These navigation agent properties are
	*  used by the navigation system to accurately plot pathing points when generating
	*  path-following behavior for AI characters  
	*/

	/** were set in editor  */
	//GetMovementComponent()->NavAgentProps.AgentHeight = 320.f;
	//GetMovementComponent()->NavAgentProps.AgentRadius = 160.f;
}

float ABossCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health <= 0.f)
		{
			SetLifeSpan(0.001f);
		}
	}

	return ActualDamage;
}

