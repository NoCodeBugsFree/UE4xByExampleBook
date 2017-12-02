// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomButtonWidget.h"
#include "ScriptingCookbook/Ch10/SCustomButton.h"

UCustomButtonWidget::UCustomButtonWidget() : Label(TEXT("Default Value"))
{

}

FReply UCustomButtonWidget::OnButtonClicked()
{
	ButtonClicked.Broadcast();
	return FReply::Handled();
}

void UCustomButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	TAttribute<FString>LabelBinding = OPTIONAL_BINDING(FString, Label);
	MyButton->Label = LabelBinding;
}

TSharedRef<SWidget> UCustomButtonWidget::RebuildWidget()
{
	MyButton = SNew(SCustomButton).ButtonClicked(BIND_UOBJECT_DELEGATE(FOnClicked, OnButtonClicked));
	return MyButton.ToSharedRef();
}
