// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API AVSGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

   /** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController. 
    * TODO remove TargetGoal and CurrentRound variables to GameState
    */
	virtual void PostLogin(APlayerController* NewPlayer);
	
private:

	/** check how many enemies we already have placed in level and store enemies amount  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetPlacedEnimiesAmount();

	/** calls to fill EnemySpawnPoints array. Reports error if we haven't any Spawn Point in the world   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void FindAndSaveAllSpawnPoints();

	/** Calls to spawn the enemy  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SpawnEnemy();

	/** use this flag to override max available enemies amount to spawn in the world  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true", DisplayName = "Override Max Enemies"))
	bool bIsMaxEnemiesNumberOverride = false;
	
    /** maximum enemies available on map */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true", EditCondition = "bIsMaxEnemiesNumberOverride"))
	int32 MaxEnemies = 20;

	/** amount of enemies we need to kill for next level  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 TargetGoal;

	/** current game round   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentRound = 1;

	/** enemies per round multiplier e.g. 3rd Round will have (CurrentRound * RoundScaleMultiplier) enemies */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 RoundScaleMultiplier = 2;

	/** maximum enemies amount to spawn  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentEnemiesAmount = 0;

	/** delay time between spawn enemies   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float SpawnDelay = 10.f;

	/** max distance from selected spawn point where enemy will be spawn   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float SpawnRadius = 5000.f; // 50 m
	
	/** all available enemy spawn points */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class AEnemySpawnPoint*> EnemySpawnPoints;

	/** Enemy Character type to spawn  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AVSEnemyCharacter> EnemyCharacterToSpawnClass;

	/** slot name to store the game data to save  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FString SaveGameSlotName = TEXT("SaveGameSlot");

	/** save game reference  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UVSSaveGame* VSSaveGame;

public:

	/** calls to update save game object when we succeeded at the round  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void UpdateSaveGameObject();

	/** returns TargetGoal */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetTargetGoal() const { return TargetGoal; }

	/** returns CurrentRound */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetCurrentRound() const { return CurrentRound; }

};
