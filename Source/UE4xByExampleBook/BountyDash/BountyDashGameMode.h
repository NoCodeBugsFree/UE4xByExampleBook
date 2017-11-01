// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BountyDashGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ABountyDashGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ABountyDashGameMode();

	void Tick(float DeltaSeconds) override;

	/**  Changes game values based on that score  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CharacterScoreUp(int32 CharacterScore);

	/** Calls to Reduce Game Speed. Reduce the game speed by GameSpeedIncrease  */
	void ReduceGameSpeed();
	
	/**  Prepares Gave Over. Sets the bGameOver flag to false  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void GameOver();

	/**  Pauses the Game  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetGamePaused(bool bNewGamePaused);

protected:

	/** Determines how many coins it take to increase the speed of the game  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NumCoinsForSpeedIncrease = 5;

	/** Determines how much faster the objects move when the NumCoinsForSpeedIncrease value has been met.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameSpeedIncrease = 5.f;

	/** Total Run time to show in HUD  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	float RunTime = 0.0f;

	/** Game Over flag */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	bool bGameOver = false;

	/** Start Game Over Count flag */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	bool StartGameOverCount = false;

	/** Simple Game Over delay */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	float TimeTillGameOver = 2.f;

	/** Current Game Over Timer */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	float GameOverTimer = 0.0f;

	/** Current game speed  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	float GameSpeed = 10.f;

	/** Current game level  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (BlueprintProtected = "true"))
	int32 GameLevel = 1;

public:

	/** Returns Inverse Game Speed  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetInverseGameSpeed() const { return -GameSpeed; }

	/** Returns Game Speed  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetGameSpeed() const { return GameSpeed; }

	/** Returns Game Level  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetGameLevel() const { return GameLevel; }

	/** Returns Run Time */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetRunTime() const { return RunTime; }

	/** Returns bGameOver flag */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	bool GetGameOver() const { return bGameOver; }
	
};
