// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserProfile.generated.h"

/**
 * UCLASS macro options sets this C++ class to be Blueprintable within the UE4 Editor
 */
UCLASS( Blueprintable, BlueprintType)
class UE4XBYEXAMPLEBOOK_API UUserProfile : public UObject
{
	GENERATED_BODY()
	
public:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	TSubclassOf<UObject> UClassOfPlayer; // Displays any UClasses
	// deriving from UObject in a dropdown menu in Blueprints
	// Displays string names of UCLASSes that derive from

	// GameMode is base class
	UPROPERTY(EditAnywhere, meta = (MetaClass = "GameMode"), Category = "AAA")
	FStringClassReference UClassGameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HpMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FString Email;
};
