// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashParticle.h"
#include "Particles/ParticleSystemComponent.h"

ABountyDashParticle::ABountyDashParticle()
{
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	check(ParticleSystemComponent);
	ParticleSystemComponent->SetupAttachment(RootComponent);

}
