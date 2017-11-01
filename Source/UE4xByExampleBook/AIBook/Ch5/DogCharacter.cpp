// Fill out your copyright notice in the Description page of Project Settings.

#include "DogCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "DogAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// Sets default values
ADogCharacter::ADogCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

// Called when the game starts or when spawned
void ADogCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &ADogCharacter::OnSeePlayer);
	}

	/** change dog's state  */
	FTimerHandle DogChangeStateTimer;
	GetWorldTimerManager().SetTimer(DogChangeStateTimer, this, &ADogCharacter::SetRandomDogState, ChangeDogStateTime, true);
}

void ADogCharacter::OnSeePlayer(APawn* Pawn)
{
	if (Pawn)
	{
		if (ADogAIController* DogAIController = Cast<ADogAIController>(GetController()))
		{
			DogAIController->GetBlackboardComponent()->SetValueAsObject("MailMan", Pawn);
			SetDogState(EDogState::DS_Barking);
		}
	}
}

void ADogCharacter::SetRandomDogState()
{
	if (DogState != EDogState::DS_Barking)
	{
		int32 RandomNumber = FMath::RandRange(0, 1);
		if(RandomNumber == 0)
		{
			SetDogState(EDogState::DS_Hungry);
		}
		else
		{
			SetDogState(EDogState::DS_Idle);
		}
	}
}

void ADogCharacter::SetDogState(EDogState NewDogState)
{
	DogState = NewDogState;

	if (ADogAIController* DogAIController = Cast<ADogAIController>(GetController()))
	{
		DogAIController->GetBlackboardComponent()->SetValueAsEnum("DogState", (uint8)DogState);
	}
}