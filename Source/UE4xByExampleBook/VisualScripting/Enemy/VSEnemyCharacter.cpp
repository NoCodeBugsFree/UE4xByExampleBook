// Fill out your copyright notice in the Description page of Project Settings.

#include "VSEnemyCharacter.h"
#include "VSEnemyAIController.h"
#include "ConstructorHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "VisualScripting/VSProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "VisualScripting/VSCharacter.h"

// Sets default values
AVSEnemyCharacter::AVSEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** set UBehaviorTree  */
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/BP_VisualScripting/BP/Enemy/VSEnemyBT"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	/** set AI Controller */
	static ConstructorHelpers::FClassFinder<AController> BPAIControllerClass(TEXT("/Game/BP_VisualScripting/BP/Enemy/BP_VSEnemyAIController"));
	if (BPAIControllerClass.Class != NULL)
	{
		AIControllerClass = BPAIControllerClass.Class;
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	/** Because the enemy have to rotate to face the running direction, The Yaw rotation needed!  */
	bUseControllerRotationYaw = true;

	/** Pawn Sensing Component  */
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	/** Damage Spheres  */
	FColor RedColor = FColor::Red;
	LeftHandDamageTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandTriggerSphere"));
	LeftHandDamageTrigger->SetSphereRadius(70.f);
	LeftHandDamageTrigger->SetupAttachment(GetMesh(), "hand_lf");

	LeftHandDamageTrigger->ShapeColor = RedColor;
	LeftHandDamageTrigger->bGenerateOverlapEvents = false;

	RightHandDamageTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandTriggerSphere"));
	RightHandDamageTrigger->SetSphereRadius(70.f);

	RightHandDamageTrigger->SetupAttachment(GetMesh(), "hand_rt");
	RightHandDamageTrigger->ShapeColor = RedColor;
	RightHandDamageTrigger->bGenerateOverlapEvents = false;

	/** intended to spawn in not attacking state  */
	bIsAttacking = false;

	/** and alive  */
	bIsDead = false;

}

// Called when the game starts or when spawned
void AVSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AVSEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/** bind sensing  */
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AVSEnemyCharacter::OnSeePawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AVSEnemyCharacter::OnHearNoise);
	

	// Register to the delegate of OnComponentBeginOverlap
	LeftHandDamageTrigger->OnComponentBeginOverlap.AddDynamic(this, &AVSEnemyCharacter::OnHandTriggerOverlap);
	RightHandDamageTrigger->OnComponentBeginOverlap.AddDynamic(this, &AVSEnemyCharacter::OnHandTriggerOverlap);
}

float AVSEnemyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		EnemyHealth -= ActualDamage;
		EnemyHealth = FMath::Clamp(EnemyHealth, 0.f, 100.f);

		/** change color according to current health value  */
		ChangeColor();
		
		// If the damage depletes our health
		if (EnemyHealth <= 0.f)
		{
			/** enable death anim  */
			bIsDead = true;

			/** disable capsule collision  */
			GetCapsuleComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

			/** disable hand damage spheres  */
			SetCanAttack(false);
			
			/** detach to stop behavior tree  */
			DetachFromControllerPendingDestroy();
			
			/** if we hit by projectile  */
			if (AVSProjectile* VSProjectile = Cast<AVSProjectile>(DamageCauser))
			{
				/** retrieve a Killer reference  */
				if (AVSCharacter* OurKiller = Cast<AVSCharacter>(VSProjectile->GetOwner()))
				{
					/** add ourself to killed targets  */
					OurKiller->AddTargetKilled();
				}
			}

			/** remove enemy cadaver  */
			SetLifeSpan(RemoveFromLevelTime);
		}
	}
	return ActualDamage;
}

void AVSEnemyCharacter::OnHandTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor != this && !OtherActor->IsPendingKill())
	{
		if (AVSCharacter* VSCharacter = Cast<AVSCharacter>(OtherActor))
		{
			VSCharacter->TakeDamage(AttackDamage, FDamageEvent(), GetController(), this);

			/** if we hit the player - disable the damage triggers  */
			SetCanAttack(false);
		}
	}
}

void AVSEnemyCharacter::ChangeColor()
{
	if (GetMesh())
	{
		if (UMaterialInstanceDynamic* DynamicMaterial = GetMesh()->CreateAndSetMaterialInstanceDynamic(0))
		{
			/** current health percentage  */
			float HealthPercentage = EnemyHealth / 100.f;
			DynamicMaterial->SetScalarParameterValue("BodyGlowIntensity", HealthPercentage);
			DynamicMaterial->SetScalarParameterValue("EyeGlowIntensity", HealthPercentage);
		}
	}
}

void AVSEnemyCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

   /**  if what we hit by is valid
	*   and we don't hit by ourself
	*   and this object don't mark to be killed
	*   and what we hit is AVSProjectile class or its child
	*/
	if (Other && Other != this && !Other->IsPendingKill() && Other->GetClass()->IsChildOf(AVSProjectile::StaticClass()))
	{
		if (AVSProjectile* VSProjectile = Cast<AVSProjectile>(Other))
		{
			TakeDamage(VSProjectile->GetDamageToCause(), FDamageEvent(), VSProjectile->GetInstigatorController(), VSProjectile);
		}
	}
}

void AVSEnemyCharacter::OnSeePawn(APawn* Pawn)
{
	/**  if we saw our character type */
	if (Pawn && Pawn->GetClass()->IsChildOf(AVSCharacter::StaticClass()))
	{
		/** and we have a valid AI Controller and Blackboard  */
		if (AVSEnemyAIController* VSEnemyAIController = Cast<AVSEnemyAIController>(GetController()))
		{
			if (UBlackboardComponent* Blackboard = VSEnemyAIController->GetBlackboardComponent())
			{
				/** save character reference to blackboard  */
				Blackboard->SetValueAsObject(PlayerName, Pawn);
			}
		}
	}
}

void AVSEnemyCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	/** get a blackboard in AI Controller  */
	if (AVSEnemyAIController* VSEnemyAIController = Cast<AVSEnemyAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComponent = VSEnemyAIController->GetBlackboardComponent())
		{
			/** save data in blackboard  */
			BlackboardComponent->SetValueAsVector(LocationOfSoundName, Location);
			BlackboardComponent->SetValueAsBool(HasHeardSoundName, true);
		}
	}
}

AActor* AVSEnemyCharacter::GetRandomPatrolPoint()
{
	/** if we have at least two Patrol Point in array to start patrol */
	if (PatrolPoints.Num() > 1)
	{
		/** get random index from zero to Num() - 1 () (as zero-bazed c++ arrays) */
		int32 RandomIndex = FMath::RandRange(0, PatrolPoints.Num() - 1);

		/** if Index valid - return object, else return nullptr  */
		if (PatrolPoints.IsValidIndex(RandomIndex))
		{
			return PatrolPoints[RandomIndex];
		}
	}
	
	/** we have less then 2 patrol points - start wandering  */
	SetEnemyState(EEnemyState::ES_Wander);

	/** we have not  Patrol Point in array  */
	return nullptr;
}

void AVSEnemyCharacter::SetCanAttack(bool NewbIsAttacking)
{
	if (NewbIsAttacking)
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

void AVSEnemyCharacter::Attack()
{
	/** set AttackingIndex for next hit  */
	AttackingIndex = FMath::RandRange(0, 1);
	bIsAttacking = true;
}

void AVSEnemyCharacter::StopAttackAnimation()
{
	bIsAttacking = false;
}