// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NSGameMode.h"
#include "NSCharacter.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API ANSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FP_Mesh;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FP_Gun;

	/** Gun mesh: 3rd person view (seen only by others) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* TP_Gun;

	/** default Character mesh intended to be Third Person Mesh */

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class USoundBase* FireSound;

	/** Sound to play each time we hit */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class USoundBase* PainSound;

	/** 3rd person anim montage asset for gun shot */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UAnimMontage* TP_FireAnimaiton;

	/** 1st person anim montage asset for gun shot */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UAnimMontage* FP_FireAnimaiton;

	/** Particle system for 1st person gun shot effect */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
	class UParticleSystemComponent* FP_GunShotParticle;

	/** Particle system for 3rd person gun shot effect */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
	class UParticleSystemComponent* TP_GunShotParticle;

	/** Particle system that will represent a bullet */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
	class UParticleSystemComponent* BulletParticle;

	/**  A predefined force-feedback effect to be played on a controller  */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UForceFeedbackEffect* HitSuccessFeedback;

	/** Current team of this player  */
	UPROPERTY(Replicated, BlueprintReadWrite, Category = Team)
	ETeam CurrentTeam;
	
protected:

	ANSCharacter();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Returns properties that are replicated for the lifetime of the actor channel */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Apply damage to this actor.
	* @see https://www.unrealengine.com/blog/damage-in-ue4
	* @param DamageAmount		How much damage to apply
	* @param DamageEvent		Data package that fully describes the damage received.
	* @param EventInstigator	The Controller responsible for the damage.
	* @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	* @return					The amount of damage actually applied.
	*/
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	/**
	* Called when this Pawn is possessed. Only called on the server (or in standalone).
	*	@param C The controller possessing this pawn
	* determines what happens when an owning-client character is possessed
	*/
	void PossessedBy(AController* NewController) override;



	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	
	// Fire RPC Fire() example
	/**
	• OnFire() executed locally on client : Begin local animation and effects, inform server of a fire
	• RPC rom client to server : FireMyWeapon()
	• Fire My Weapon received on server : Perform ray - trace to see whether anything was hit and inform clients to play PlayerFired visuals
	• RPC From Server To All connected Clients : PlayerFiredVisuals()
	• PlayerFiredVisuals Received on all connected Clients : Spawn and play particle emitters for gunshot and sounds for gunshot
	*/

	/** Fires a virtual projectile. */
	void OnFire(); 
		
	// Will be called by the server to perform raytrace
	void Fire(const FVector Position, const FVector Direction);

	// -----------------------------------------------------------------------------------

	/** Will be used to set custom base colors on the mesh material so we can use the same material for both the blue and red teams!  */
	class UMaterialInstanceDynamic* DynamicCharacterMaterial;

	/** Player State reference  */
	class ANSPlayerState* NSPlayerState;
	
private:

	/** Per hit weapon damage  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float WeaponDamage = 101.f;

	/** REMOTE PROCEDURE CALLS */

	/** Perform fire action on the server  */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire(const FVector Position, const FVector Direction);
	bool ServerFire_Validate(const FVector Position, const FVector Direction);
	void ServerFire_Implementation(const FVector Position, const FVector Direction);
	
	/** Multicast so all clients run shoot effects  */
	UFUNCTION(NetMulticast, Unreliable)
	void MultiCastShootEffects();
	void MultiCastShootEffects_Implementation();
	
	/** Called on death for all clients for hilarious death  */
	UFUNCTION(NetMulticast, Unreliable)
	void MultiCastRagdoll();
	void MultiCastRagdoll_Implementation();
	
	/** Play pain on owning client when hit  */
	UFUNCTION(Client, Reliable)
	void PlayPain();
	void PlayPain_Implementation();

	/** Plays FP anim and particles if specified  */
	void PlayFirstPersonEffects();

public:

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return FP_Mesh; }

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetFP_GunMesh() const { return FP_Gun; }

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** Returns  current player state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	class ANSPlayerState* GetNSPlayerState();

	/** Sets the player state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetNSPlayerState(class ANSPlayerState* NewPlayerState);

	/** Respawn dead character  */
	void Respawn();

	// Set's team color
	UFUNCTION(NetMulticast, Reliable)
	void SetTeam(ETeam NewTeam);
	void SetTeam_Implementation(ETeam NewTeam);
	
};
