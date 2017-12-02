// Fill out your copyright notice in the Description page of Project Settings.

#include "TalkingPawn.h"
#include "Talker.h"
#include "Components/BoxComponent.h"
#include "TalkingMesh.h"

ATalkingPawn::ATalkingPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	TalkCollider = CreateDefaultSubobject<UBoxComponent>("TalkCollider");
	TalkCollider->SetBoxExtent(FVector(200, 200, 100));
	TalkCollider->OnComponentBeginOverlap.AddDynamic(this, &ATalkingPawn::OnTalkOverlap);
	TalkCollider->SetupAttachment(RootComponent);
}

void ATalkingPawn::OnTalkOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor != this && !OtherActor->IsPendingKill() && OtherActor->GetClass()->ImplementsInterface(UTalker::StaticClass()))
	{
		if (ITalker* Talker = Cast<ITalker>(OtherActor))
		{
			Talker->Execute_StartTalking(OtherActor);
			Talker->Execute_StartCrying(OtherActor, FVector(1.f), 222);
		}
	}
}