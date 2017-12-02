// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "ScriptingCookbook/ScriptingCookbookGameMode.h"

// Sets default values
AMyTriggerVolume::AMyTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	SetRootComponent(TriggerZone);
}

// Called when the game starts or when spawned
void AMyTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyTriggerVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor)
	{
		if(AScriptingCookbookGameMode* ScriptingCookbookGameMode = Cast<AScriptingCookbookGameMode>(GetWorld()->GetAuthGameMode()))
		{
			ScriptingCookbookGameMode->MyParameterDelegate.ExecuteIfBound(FLinearColor::Green);
			ScriptingCookbookGameMode->MyStandardDelegate.ExecuteIfBound();
			ScriptingCookbookGameMode->MyMulticastDelegate.Broadcast();
		}

		OnPlayerEntered.Broadcast();
	}
}

void AMyTriggerVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

