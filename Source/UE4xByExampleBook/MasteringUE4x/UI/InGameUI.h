// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	/**  call from player to start playing Coin animation when coin is collected */
	void PlayCoinAnimation();

private:

	/** call in NativeTick function to update HUD to valid state  */
	void UpdateHUD();
	
	/** calls when widget is constructed  */
	void NativeConstruct() override;
	
	/** call every frame  */
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

   /** calls to bind BP created animation "CoinValueChange"
	*  with c++ pointer UWidgetAnimation* AddCoinAnim to further c++ work
	*/
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetCoinAnimReference(UWidgetAnimation* NewAnim) { AddCoinAnim = NewAnim; }

   /** calls to find animations created in InGameUI Widget BP
	*  loops through UProperty*
	*/
	void AssignAnimations();
	
	/** widget owner character reference  */
	class AGladiator* WidgetOwnerCharacter;
	
	/** Health Percentage to bind  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float HealthPercentage;

	/** Coins Text to bind */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FText  CoinsText;

	/** Coins Text to bind */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UWidgetAnimation* AddCoinAnim;

	/** Coin Value Change Anim Name in Blueprint  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FString CoinValueChange_AnimName = "CoinValueChange";
	
};
