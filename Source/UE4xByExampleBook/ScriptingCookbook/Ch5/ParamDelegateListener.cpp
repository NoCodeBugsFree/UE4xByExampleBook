// Fill out your copyright notice in the Description page of Project Settings.

#include "ParamDelegateListener.h"
#include "Components/PointLightComponent.h"
#include "ScriptingCookbook/ScriptingCookbookGameMode.h"

// Sets default values
AParamDelegateListener::AParamDelegateListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	SetRootComponent(PointLightComponent);
}

// Called when the game starts or when spawned
void AParamDelegateListener::BeginPlay()
{
	Super::BeginPlay();
	
	if(AScriptingCookbookGameMode* ScriptingCookbookGameMode = Cast<AScriptingCookbookGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ScriptingCookbookGameMode->MyParameterDelegate.BindUObject(this, &AParamDelegateListener::SetLightColor, true);
	}
}

// Called every frame
void AParamDelegateListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParamDelegateListener::SetLightColor(FLinearColor LightColor, bool bEnableLight)
{
	if (PointLightComponent)
	{
		PointLightComponent->SetLightColor(LightColor);
		PointLightComponent->SetVisibility(bEnableLight);
	}
}

