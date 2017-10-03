// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameUI.h"
#include "MasteringUE4x/Gladiator.h"
#include "Animation/WidgetAnimation.h"

void UInGameUI::UpdateHUD()
{
	if (WidgetOwnerCharacter)
	{
		/** retrieve all data from owner character  */
		WidgetOwnerCharacter->GetHUDData(HealthPercentage, CoinsText);
	}
}

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	/** sets owner reference  */
	WidgetOwnerCharacter = Cast<AGladiator>(GetOwningPlayerPawn());

	/**  fun way to find BP created animations */
	// AssignAnimations();
}

void UInGameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateHUD();
}

void UInGameUI::AssignAnimations()
{
	/** In memory only: Linked list of properties from most-derived to base */
	UProperty* Property = GetClass()->PropertyLink;

	// GO through Linked list until end (NULL)
	while (Property)
	{
		// is our Property ObjectProperty or its child ?
		if (Property->GetClass()->IsChildOf(UObjectProperty::StaticClass()))
		{
			if(UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
			{
				// Only want the properties that are widget animations
				if (ObjectProperty->PropertyClass->IsChildOf(UWidgetAnimation::StaticClass()))
				{
					/**   */
					UObject* Object = ObjectProperty->GetObjectPropertyValue_InContainer(this);

					/**   */
					if (UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(Object))
					{
						FString TestString;

						WidgetAnimation->GetFName().ToString(TestString);

						if (TestString.Contains(CoinValueChange_AnimName))
						{
							UE_LOG(LogTemp, Error, TEXT("Contains"));

							AddCoinAnim = WidgetAnimation;
						}

						// AddCoinAnim = widgetAnim;

						// DO SOMETHING TO STORE OFF THE ANIM PTR HERE!
						// E.g. add to a TArray of some struct that holds info for each anim

						// Useful note : GetFName() on a UWidgetAnimation returns the name assigned
						// in UMG editor with "_INST" appended.You can use GetFName() on the UProperty 
						// to get the name as set in UMG.
					}
				}
			}
		}

		/** next member in Linked list  */
		Property = Property->PropertyLinkNext;
	}
}

void UInGameUI::PlayCoinAnimation()
{
	if (AddCoinAnim)
	{
		PlayAnimation(AddCoinAnim);
	}
}
