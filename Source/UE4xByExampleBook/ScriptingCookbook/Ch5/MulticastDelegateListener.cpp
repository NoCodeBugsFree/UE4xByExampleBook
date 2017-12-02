// Fill out your copyright notice in the Description page of Project Settings.

#include "MulticastDelegateListener.h"
#include "Components/PointLightComponent.h"
#include "ScriptingCookbook/ScriptingCookbookGameMode.h"

// Sets default values
AMulticastDelegateListener::AMulticastDelegateListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	SetRootComponent(PointLightComponent);
}

// Called when the game starts or when spawned
void AMulticastDelegateListener::BeginPlay()
{
	Super::BeginPlay();

	if (AScriptingCookbookGameMode* ScriptingCookbookGameMode = Cast<AScriptingCookbookGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ScriptingCookbookGameMode->MyMulticastDelegate.AddUObject(this, &AMulticastDelegateListener::ToggleLight);
	}	
}

void AMulticastDelegateListener::ToggleLight()
{
	if (PointLightComponent)
	{
		PointLightComponent->ToggleVisibility();
	}
}

// Called every frame
void AMulticastDelegateListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

