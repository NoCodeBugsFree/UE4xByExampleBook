// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SlateDelegates.h"
#include "CustomButtonWidget.generated.h"


DECLARE_DYNAMIC_DELEGATE_RetVal(FString, FGetString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClicked);

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UCustomButtonWidget : public UWidget
{
	GENERATED_BODY()
	
	
public:

	UCustomButtonWidget();

	UPROPERTY(BlueprintAssignable)
	FButtonClicked ButtonClicked;

	FReply OnButtonClicked();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Label;

	UPROPERTY()
	FGetString LabelDelegate;

	virtual void SynchronizeProperties() override;

protected:

	TSharedPtr<class SCustomButton> MyButton;

	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	
};
