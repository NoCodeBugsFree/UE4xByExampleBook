// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** calls only when owner took damage  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void UpdateHUD(float NewHealthBarPercentage);

private:
	
	/** health bar percent  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float HealthBarPercentage = 0.33f;
		
};
