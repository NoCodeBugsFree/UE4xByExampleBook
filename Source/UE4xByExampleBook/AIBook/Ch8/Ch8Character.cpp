// Fill out your copyright notice in the Description page of Project Settings.

#include "Ch8Character.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ConstructorHelpers.h"
#include "Ch8AIController.h"

// Sets default values
ACh8Character::ACh8Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/** health text  */
	CharText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Char Text"));
	CharText->SetupAttachment(RootComponent);
	CharText->SetHorizontalAlignment(EHTA_Center);
	CharText->SetTextRenderColor(FColor::Orange);
	CharText->SetRelativeLocation(FVector(0, 0, 100));

	/** camera boom  */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	/** camera  */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	/** set behavior tree asset */
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/AIBook/BP/Ch8/AI/EnemyAI"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
}

void ACh8Character::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetHealthText();
}

float ACh8Character::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health <= 0.f && !IsPendingKill())
		{
			Destroy();
		}
	}

	return ActualDamage;
}

// Called every frame
void ACh8Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHealthText();
}

void ACh8Character::SetHealthText() const
{
	const FString StringHealth = FString::Printf(TEXT("Health: %f"), Health);
	const FText HealthText = FText::FromString(StringHealth);
	CharText->SetText(HealthText);
}

