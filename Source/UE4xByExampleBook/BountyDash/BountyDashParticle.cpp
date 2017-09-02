// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashParticle.h"
#include "Particles/ParticleSystemComponent.h"

ABountyDashParticle::ABountyDashParticle()
{
	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	check(particleSystem);
	particleSystem->SetupAttachment(RootComponent);

}
