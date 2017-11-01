// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_NullifyMailMan.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DogCharacter.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"

UBTService_NullifyMailMan::UBTService_NullifyMailMan()
{
	MailMan.SelectedKeyName = "MailMan";
	NodeName = FString("Nullify Mail Man");
	Interval = 3.f;
	RandomDeviation = 0.5f;
}

void UBTService_NullifyMailMan::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ADogCharacter* DogCharacter = Cast<ADogCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{	
		/**Nullify Mail Man BB var   */
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(MailMan.SelectedKeyName, nullptr);
	}
}
