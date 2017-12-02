// Fill out your copyright notice in the Description page of Project Settings.

#include "DelegateListener.h"
#include "Components/PointLightComponent.h"
#include "ScriptingCookbook/ScriptingCookbookGameMode.h"

// Sets default values
ADelegateListener::ADelegateListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	SetRootComponent(PointLight);
	PointLight->SetVisibility(false);
}

// Called when the game starts or when spawned
void ADelegateListener::BeginPlay()
{
	Super::BeginPlay();

	if(AScriptingCookbookGameMode* ScriptingCookbookGameMode = Cast<AScriptingCookbookGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ScriptingCookbookGameMode->MyStandardDelegate.BindUObject(this, &ADelegateListener::EnableLight);
	}
}

void ADelegateListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (AScriptingCookbookGameMode* ScriptingCookbookGameMode = Cast<AScriptingCookbookGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ScriptingCookbookGameMode->MyStandardDelegate.Unbind();
	}
}

// Called every frame
void ADelegateListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADelegateListener::EnableLight()
{
	if (PointLight)
	{
		PointLight->SetVisibility(true);
	}
}
