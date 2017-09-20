// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NSGameMode.h"
#include "NSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UE4XBYEXAMPLEBOOK_API ANSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	/** Returns Team   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	ETeam GetTeam() const { return Team; }

	/** Returns Health   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetHealth() const { return Health; }

	/** Returns Deaths   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	uint8 GetDeaths() const { return Deaths; }

	
	/** Increment Score   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void AddScore() { Score += 1.f; }

	/** Increment Deaths   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void AddDeaths() { Deaths++; }

	/** Add some Health   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void AddHealth(float HealthToAdd) { Health += HealthToAdd; }

	/** Reinitialize characters health for respawning  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ReinitializeHealth() { Health = 100.f; }

	/**Sets the new Team state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetTeam(ETeam NewTeam) { Team = NewTeam; }

private:
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Health = 100.f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint8 Deaths = 0;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	ETeam Team = ETeam::BLUE_TEAM;
	
};
