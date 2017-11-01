// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPatrolCharacter.h"
#include "Perception/AIPerceptionComponent.h"

// Sets default values
AEnemyPatrolCharacter::AEnemyPatrolCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	
}

// Called when the game starts or when spawned
void AEnemyPatrolCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyPatrolCharacter::OnUpdatePerception);
	}
}

// Called every frame
void AEnemyPatrolCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPatrolCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPatrolCharacter::OnUpdatePerception(TArray<AActor*> UpdatedActors)
{
	UE_LOG(LogTemp, Error, TEXT("OnUpdatePerception!"));
}

