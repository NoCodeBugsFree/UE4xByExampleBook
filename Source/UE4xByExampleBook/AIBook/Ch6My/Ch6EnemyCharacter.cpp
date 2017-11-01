// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch6EnemyCharacter.h"
#include "ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "Ch6AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EngineUtils.h"
#include "Ch6TargetPoint.h"


// Sets default values
ACh6EnemyCharacter::ACh6EnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/** set default AI Controller */
	static ConstructorHelpers::FClassFinder<AController> BPAIControllerClass(TEXT("/Game/AIBook/BP/Ch6/MyVersionCH6/BP_Ch6AIController"));
	if (BPAIControllerClass.Class != NULL)
	{
		AIControllerClass = BPAIControllerClass.Class;
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/AIBook/BP/Ch6/MyVersionCH6/Ch6_BT.Ch6_BT"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

// Called when the game starts or when spawned
void ACh6EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/** bind pawn sensing  */
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &ACh6EnemyCharacter::OnSeePlayer);
		PawnSensingComponent->OnHearNoise.AddDynamic(this, &ACh6EnemyCharacter::OnHearNoise);
	}

	
	/** attempt to find target point   */
	for (TActorIterator<ACh6TargetPoint> Iter(GetWorld()); Iter; ++Iter)
	{
		if ((*Iter))
		{
			CurrentPatrolPoint = *Iter;
			return;
		}	
	}

	/** if we haven't target point - go wander  */
	if (!CurrentPatrolPoint)
	{
		if(ACh6AIController* Ch6AIController = Cast<ACh6AIController>(GetController()))
		{
			Ch6AIController->SetState(ECh6EnemyState::ECh6_Wander);
		}
	}
}

void ACh6EnemyCharacter::OnSeePlayer(APawn* Pawn)
{
	if (ACh6AIController* Ch6AIController = Cast<ACh6AIController>(GetController()))
	{
		if (Ch6AIController->GetBlackboardComponent() && Pawn)
		{
			Ch6AIController->GetBlackboardComponent()->SetValueAsObject("Enemy", Pawn);
			Ch6AIController->SetState(ECh6EnemyState::ECh6_Attack);
		}
	}
}

void ACh6EnemyCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (ACh6AIController* Ch6AIController = Cast<ACh6AIController>(GetController()))
	{
		if (Ch6AIController->GetBlackboardComponent() && PawnInstigator)
		{
			Ch6AIController->GetBlackboardComponent()->SetValueAsVector("NoiseLocation", PawnInstigator->GetActorLocation());
			Ch6AIController->SetState(ECh6EnemyState::ECh6_Suspicious);
		}
	}

}

void ACh6EnemyCharacter::SetCurrentPatrolPoint(class ACh6TargetPoint* NewTargetPoint)
{
	CurrentPatrolPoint = NewTargetPoint;
}
