// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PhysicsBall.generated.h"

UCLASS()
class UE4XBYEXAMPLEBOOK_API APhysicsBall : public APawn
{
	GENERATED_BODY()
	
	/* Ball static mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BallMesh;

	/*  Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	
	/* Spring Arm Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	
	/*  Sphere Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

public:

	/** calls to set a new follower for this ball  */
	void SetFollower(APhysicsBall* NewFollower);
	
protected:

	// Sets default values for this pawn's properties
	APhysicsBall();
	
	/**
	* Called when this Pawn is possessed. Only called on the server (or in standalone).
	*	@param C The controller possessing this pawn
	*/
	void PossessedBy(AController* NewController) override;
	
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

private:

	/** Calls in tick to calculate and set leader direction   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetLeaderDirection();

	/** Calls in tick for each overlapped ball finds leaders and followers, and calculate behavior for all nearby agents */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ForEachOverlapped();

	/** finds and sets leader and follower for this ball  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void FindLeaderAndFollower(APhysicsBall* PhysicsBall);

	/** sets NAlignment, NCohesion and NSeperation for this ball according all nearby agents  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CalculateBehaviorForNearbyAgents(APhysicsBall* PhysicsBall);

	/** tweaks NAlignment, NCohesion and NSeperation for this ball according amount of all nearby agents  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetupFlockingBehavior();

	/** calls to add another Physics Ball to OverlappedPhysicsBalls array  */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	/** calls to remove another Physics Ball from OverlappedPhysicsBalls array  */
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/** reset ball location and reset its movement direction  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ResetBall();

	/** create HUD widget  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CreateHUD(AController* NewController);

	/** sets NCohesion, NAlignment and NSeperation to FVector::ZeroVectors  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ClearValues();

	/** calls in tick to rotate spring arm smoothly according movement  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void RotateSpringArmAccordingMovement(float DeltaTime);

   /** calls in tick to calculates the direction value
	*  WTF is 	BP_ZeroVector ???
	*/
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CalculateDirection();

	/** calls in tick to apply torque to a ball */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void ApplyTorqueToBall();

	/** calls in tick to check should we bounce or not */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Bounce();
	
	// -----------------------------------------------------------------------------------

	/** all another Physics Balls in reachable radius  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> OverlappedPhysicsBalls;

	/** torque to apply to ball mesh  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float RollTorque = 50000000.0f;
	
	/** direction of movement  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FVector Direction;

	/** initial location of this pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FVector StartLocation;

	/** Current amount of cohesion for this ball  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FVector NCohesion;

	/**  Current amount of alignment for this ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FVector NAlignment;

	/** Current amount of separation for this ball  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FVector NSeperation;

	/** Leader for this ball (can be nullptr)  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	APhysicsBall* Leader;

	/** Follower for this ball (can be nullptr)  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	APhysicsBall* Follower;

	/** shows whether this ball is a leader or not   */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	bool bIsLeader = false;

	/** WTF ??? never used in book BP
	 * direction for leader movement ???  
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FVector LeaderDirection;

	/** HUD User Widget Template  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** Current HUD Widget reference  */
	UPROPERTY()
	class UUserWidget* CurrentWidget;

	/** game mode reference  */
	class APhysicsBallGameModeBase* PhysicsBallGameMode;

public:

	/** returns current direction  */
	FVector GetDirection() const { return Direction; }
	
};
