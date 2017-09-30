// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "ConstructorHelpers.h"
#include "Engine/Blueprint.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "MasteringUE4x/Gladiator.h"
#include "BearAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	static ConstructorHelpers::FObjectFinder<class UBlueprint> BPAIControllerClass(TEXT("/Game/MasteringUE4x/BP/Enemy/BP_BearAIController"));
	if (BPAIControllerClass.Succeeded())
	{
		AIControllerClass = BPAIControllerClass.Object->GeneratedClass;
	}
	
	static ConstructorHelpers::FObjectFinder<class UObject> BT(TEXT("/Game/MasteringUE4x/BP/Enemy/BearBT"));
	if (BT.Succeeded())
	{
		BehaviorTree = Cast<UBehaviorTree>(BT.Object);
	}
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	/** Because the enemy have to rotate to face the running direction, The Yaw rotation needed!  */
	bUseControllerRotationYaw = true;

	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensor"));
	PawnSensor->SensingInterval = .25f; // 4 times per second
	PawnSensor->bOnlySensePlayers = true;
	PawnSensor->SetPeripheralVisionAngle(85.f);

	BodySphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("BodyTriggerSphere"));
	BodySphereTrigger->SetSphereRadius(150.f);
	BodySphereTrigger->SetupAttachment(GetMesh());

	FColor BlueColor = FColor::Blue;
	LeftHandDamageTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandTriggerSphere"));
	LeftHandDamageTrigger->SetSphereRadius(70.f);
	LeftHandDamageTrigger->SetupAttachment(GetMesh(), "hand_lf");

	LeftHandDamageTrigger->ShapeColor = BlueColor;
	LeftHandDamageTrigger->bGenerateOverlapEvents = false;

	RightHandDamageTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandTriggerSphere"));
	RightHandDamageTrigger->SetSphereRadius(70.f);
	
	RightHandDamageTrigger->SetupAttachment(GetMesh(), "hand_rt");
	RightHandDamageTrigger->ShapeColor = BlueColor;
	RightHandDamageTrigger->bGenerateOverlapEvents = false;
	
	/** 
		Just make sure to not use the Enemy::Character capsule as the
		navigation collision, and use the agent and set its radius to
		something fits the enemy size
		//the main goal is to avoid as much as possible the cases when the
		enemy meshes intersecting with each other, or with the environment  
	*/

	/** Radius of the capsule used for navigation/pathfinding. */
	GetCharacterMovement()->NavAgentProps.AgentRadius = 400.f;

	/** using the character collision for the navigations.  */
	GetCharacterMovement()->SetUpdateNavAgentWithOwnersCollisions(false);
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/** PawnSensor delegates */
	PawnSensor->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
	PawnSensor->OnHearNoise.AddDynamic(this, &AEnemyCharacter::OnHearNoise);

	// Register to the delegate of OnComponentBeginOverlap
	LeftHandDamageTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnHandTriggerOverlap);
	RightHandDamageTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnHandTriggerOverlap);
	
}

void AEnemyCharacter::OnPerformAttack()
{
	AttackingIndex = FMath::RandRange(0, 1);
	bIsAttacking = true;
}

void AEnemyCharacter::OnPreAttack()
{
	/** enable spheres overlap event  */
	SetCanAttack(true);
}

void AEnemyCharacter::OnPostAttack()
{
	/** disable spheres overlap event  */
	SetCanAttack(false);

	bIsAttacking = false;
}

void AEnemyCharacter::OnHandTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor != this && !OtherActor->IsPendingKill())
	{
		if (AGladiator* Gladiator = Cast<AGladiator>(OtherActor))
		{
			//Gladiator->TakeDamage(AttackDamage, FDamageEvent(), GetController(), this);

			/** in case it hit the player, it is good idea to disable the
				triggers, this way we'll make sure that the triggers will not over
				calculate with each single hit  */
			SetCanAttack(false);

			Gladiator->OnChangeHealthByAmount(AttackDamage);
		}
	}
}

void AEnemyCharacter::OnHearNoise(APawn *OtherActor, const FVector& Location, float Volume)
{

}

void AEnemyCharacter::OnSeePawn(APawn *OtherPawn)
{
	
}

void AEnemyCharacter::SetCanAttack(bool bCanAttack)
{
	if (bCanAttack)
	{
		LeftHandDamageTrigger->bGenerateOverlapEvents = true;
		RightHandDamageTrigger->bGenerateOverlapEvents = true;
	} 
	else
	{
		LeftHandDamageTrigger->bGenerateOverlapEvents = false;
		RightHandDamageTrigger->bGenerateOverlapEvents = false;
	}
}

