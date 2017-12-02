// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScriptingCookbook/Ch7/MyInterface.h"
#include "HttpModule.h"
#include "HttpManager.h"
#include "HttpRetrySystem.h"
#include "ScriptingCookbookGameMode.generated.h"


/** 
	TODO ch8 can't create module !
	TODO all relative to modules creation
	TODO http
*/

DECLARE_DELEGATE(FStandardDelegateSignature)
DECLARE_DELEGATE_OneParam(FParamDelegateSignature, FLinearColor)
DECLARE_MULTICAST_DELEGATE(FMulticastDelegateSignature)

UCLASS()
class UE4XBYEXAMPLEBOOK_API AScriptingCookbookGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	void Style();

	void DataBinding();

	void BindClickEvent();

	TArray<IMyInterface*> MyInterfaceInstances;

	FStandardDelegateSignature MyStandardDelegate;

	FParamDelegateSignature MyParameterDelegate;

	FMulticastDelegateSignature MyMulticastDelegate;
	
	/** new object template  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserProfile> UPBlueprintClassName;

	/** new object template  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UAction> ActionTemplate;

	// ---------- ToggleHUD demo ----------------------------------------------------------------

	

	void ToggleHUD();

	UPROPERTY()
	FTimerHandle HUDToggleTimer;

	TSharedPtr<SVerticalBox> widget;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// ---------- Attaching function calls to Slate events - Click Event ------------------------------------------------

private:


	class ALandscape* Landscape;

	TSharedPtr<SVerticalBox> Widget;
	TSharedPtr<STextBlock> ButtonLabel;

	FReply ButtonClicked();

	// -------- Use Data Binding with Unreal Motion Graphics ------------------------------

private:
	
	FText GetButtonLabel() const;
};
