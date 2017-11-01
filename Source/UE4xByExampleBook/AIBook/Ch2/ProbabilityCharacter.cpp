// Fill out your copyright notice in the Description page of Project Settings.

#include "ProbabilityCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController_Probability.h"

// Sets default values
AProbabilityCharacter::AProbabilityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	

}

// Called when the game starts or when spawned
void AProbabilityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AProbabilityCharacter::OnSeePlayer);
	}
}

// Called every frame
void AProbabilityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AProbabilityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AProbabilityCharacter::OnSeePlayer(APawn* Pawn)
{
	bool bShouldAttack = FMath::RandBool();

	if(AAIController_Probability* AIController_Probability = Cast<AAIController_Probability>(GetController()))
	{
		if (bShouldAttack)
		{
			AIController_Probability->SetEnemyState(EState::S_Attack);
		}
		else
		{
			AIController_Probability->SetEnemyState(EState::S_Flee);
		}
	}
}

