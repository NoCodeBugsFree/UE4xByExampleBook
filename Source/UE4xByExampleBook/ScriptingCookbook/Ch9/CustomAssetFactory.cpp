// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomAssetFactory.h"
#include "MyCustomAsset.h"

UCustomAssetFactory::UCustomAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMyCustomAsset::StaticClass();
}

UObject* UCustomAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	auto NewObjectAsset = NewObject<UMyCustomAsset>(InParent, InClass, InName, Flags);
	return NewObjectAsset;
}
