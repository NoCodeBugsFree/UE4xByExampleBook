// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;
	
protected:

	// Sets default values for this character's properties
	ABossCharacter();
	
	/** Calls when this character is damaged  */
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
private:

	/** Character's health  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Health = 100.f;
	
	/*   Scene Component for attract a projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSceneComponent;

	/** sets the boss state according current boss health  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetStateAccordingCurrentHealth();

public:

	/** retunrs projectile scene component **/
	FORCEINLINE class USceneComponent* GetProjectileSceneComponent() const { return ProjectileSceneComponent; }
	
	/** Returns current character's health  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetHealth() const { return Health; }
};
