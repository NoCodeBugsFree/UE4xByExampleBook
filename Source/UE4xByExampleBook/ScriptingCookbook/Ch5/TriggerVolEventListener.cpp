// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerVolEventListener.h"
#include "Components/PointLightComponent.h"
#include "ScriptingCookbook/Ch5/MyTriggerVolume.h"

// Sets default values
ATriggerVolEventListener::ATriggerVolEventListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	SetRootComponent(PointLightComponent);
}

// Called when the game starts or when spawned
void ATriggerVolEventListener::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerEventSource)
	{
		TriggerEventSource->OnPlayerEntered.AddUObject(this, &ATriggerVolEventListener::OnTriggerEvent);
	}
}

void ATriggerVolEventListener::OnTriggerEvent()
{
	PointLightComponent->SetLightColor(FLinearColor(0, 1, 0, 1));
}

// Called every frame
void ATriggerVolEventListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

