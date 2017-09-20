// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NSGameMode.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class ETeam : uint8
{
	BLUE_TEAM,
	RED_TEAM
};

UCLASS()
class UE4XBYEXAMPLEBOOK_API ANSGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ANSGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/** 
		Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController.
		 This method will be called whenever a new client joins the server session
		and will parse the new PlayerController that has connected
	*/
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Overridable function called whenever this actor is being removed from a level
	 *
	 * Here we simply ensure that play is not being ended for map traveling reasons and
	 * that it is in fact either a definite quit event or end PIE session event. If so, we are to
     * reset our static Boolean flag "bInGameMenu" so the game always starts in menu.
	 */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Calls to respawn the player after death  */
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "AAA")
	void Respawn(class ANSCharacter* Character);

	/** Calls to spawn the player initially  */
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "AAA")
	void Spawn(class ANSCharacter* Character);
	
private:

	/** Red Team members */
	TArray<class ANSCharacter*> RedTeam;

	/** Blue Team members */
	TArray<class ANSCharacter*> BlueTeam;

	/** Red Spawn Points  */
	TArray<class ANSSpawnPoint*> RedSpawns;

	/** Blue Spawn Points  */
	TArray<class ANSSpawnPoint*> BlueSpawns;

	/** Characters that we need to spawn  */
	TArray<class ANSCharacter*> ToBeSpawned;

	/** this flag shows whether match has started or not  */
	bool bGameStarted;

	/** to remain in memory during server travel  */
	static bool bInGameMenu;
	
};
