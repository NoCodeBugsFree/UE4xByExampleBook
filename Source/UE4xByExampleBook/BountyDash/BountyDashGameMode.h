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

	void CharScoreUp(unsigned int CharScore);

	UFUNCTION()
	float GetInvGameSpeed();

	UFUNCTION()
	float GetGameSpeed();

	UFUNCTION()
	int32 GetGameLevel();

	void ReduceGameSpeed();

	virtual void Tick(float DeltaSeconds) override;

	float GetRunTime() const { return RunTime; }

	UFUNCTION()
	bool GetGameOver();

	UFUNCTION()
	void GameOver();

	UFUNCTION()
	void SetGamePaused(bool gamePaused);

protected:

	/** determine how many coins it take to increase the speed of the game  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NumCoinsForSpeedIncrease;

	/** determine how much faster the objects move when the NumCoinsForSpeedIncrease value has been met.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameSpeedIncrease;

	UPROPERTY()
	float RunTime;

	UPROPERTY()
	bool bGameOver;

	UPROPERTY()
	bool startGameOverCount;

	UPROPERTY()
	float timeTillGameOver;

	UPROPERTY()
	float gameOverTimer;

private:
	
	UPROPERTY()
	float GameSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 GameLevel;
	
};
