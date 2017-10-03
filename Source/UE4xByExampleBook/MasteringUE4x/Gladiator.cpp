// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "Engine/DataTable.h"
#include "PickupBase.h"
#include "CoinPickup.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UI/InGameUI.h"
#include "BellzSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameDataTables.h"
#include "EngineUtils.h"

// Sets default values
AGladiator::AGladiator()
{
	/** sets Game UI Widget BP  */
	static ConstructorHelpers::FClassFinder<UUserWidget> GameUIWidgetClass(TEXT("/Game/MasteringUE4x/BP/UI/BP_InGameUI"));
	if (GameUIWidgetClass.Class != NULL)
	{
		GameUIWidget = GameUIWidgetClass.Class;
	}

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configure character movement

	/** Character moves in the direction of input...  */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = JumpingVelocity;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;

	// Rotate the arm based on the controller
	CameraBoom->bUsePawnControlRotation = true; 

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// by default the inputs should be enabled, in case there is something need to be tested
	OnSetPlayerController(true);
}

// Called when the game starts or when spawned
void AGladiator::BeginPlay()
{
	Super::BeginPlay();

	/** creates in game HUD Widget BP  */
	CreateHUD();
	
	/** loads the game */
	LoadGameFromSlot();
	
	/** find our GameDataTable object in the world and  Fetch All Tables from it */
	SetupGameDataTables();

}


// Called every frame
void AGladiator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGladiator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Collect", IE_Pressed, this, &AGladiator::OnCollectPickup);

	InputComponent->BindAction("Attack", IE_Released, this, &AGladiator::OnAttack);

	InputComponent->BindAction("ChangeWeapon", IE_Released, this, &AGladiator::OnChangeWeapon);

	InputComponent->BindAxis("MoveForward", this, &AGladiator::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGladiator::MoveRight);
	
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AGladiator::TurnAtRate);

	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this,&AGladiator::LookUpAtRate);

}

void AGladiator::OnSetPlayerController(bool Status)
{
	IsControlable = Status;
}

void AGladiator::OnChangeHealthByAmount(float UsedAmount)
{
	// TotalHealth -= UsedAmount; // ? WTF ?
	CurrentHealth -= UsedAmount;

	/**  there is a call for an internal function being made using the method
		CallFunctionByNameWithArguments ; this means that the C++ code is going to call
		the blueprint function.
	*/
	FOutputDeviceNull ar;
	CallFunctionByNameWithArguments(TEXT("ApplyGetDamageEffect"), ar, NULL, true);

	/** Command line. 
	
	bool UObject::CallFunctionByNameWithArguments(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec = false);
	
	The function being called here, which is called ApplyGetDamageEffect , is meant to
	display an overall screen effect that shows that the player has taken some damage at
	that moment. We will build its logic in the blueprint later in this chapter, but let's be
	clear about what exactly this function is going to do in order:
		1. Get the level post-processing volume that is dedicated to displaying the hit
	effect and save a reference to it so it becomes easier and faster the next time
	we call the function, as we will already have a reference for the volume and
	then will display this volume effect.
		2. Get the sprite component we created in the header file, enable it, and play
	some fade animations for it. So yeah, making fade effects based on a float
	value is a lot easier through blueprints and timeline nodes.
		3. Finally we create some camera shakes to simulate the damage to the player.
	Once we're done with the C++ code and have created our blueprint based on that
	class, we will be working on beautifying it and adding some blueprint logic. That's
	where we will implement the logic for the ApplyGetDamageEffect method.
	
	*/


	/** save current health value to slot   */
	SaveGameToSlot();
}

void AGladiator::SaveGameToSlot()
{
	if (UBellzSaveGame* BellzSaveGame = Cast<UBellzSaveGame>(UGameplayStatics::CreateSaveGameObject(UBellzSaveGame::StaticClass())))
	{
		/** Change the health value of the save class to match the current health value of the gladiator  */
		BellzSaveGame->PlayerHealth = CurrentHealth;
		BellzSaveGame->CollectedCoins = CollectedCoins;

		/**  Store the health value to the save file */
		UGameplayStatics::SaveGameToSlot(BellzSaveGame, BellzSaveGame->SlotName, BellzSaveGame->PlayerIndex);
	}
}

void AGladiator::LoadGameFromSlot()
{
	if (UBellzSaveGame* BellzLoadGameInstance = Cast<UBellzSaveGame>(UGameplayStatics::CreateSaveGameObject(UBellzSaveGame::StaticClass())))
	{
		BellzLoadGameInstance = Cast<UBellzSaveGame>(UGameplayStatics::LoadGameFromSlot(BellzLoadGameInstance->SlotName,
			BellzLoadGameInstance->PlayerIndex));

		// get the needed value and store it in a local variable
		if (BellzLoadGameInstance->PlayerHealth > 0)
		{
			CurrentHealth = BellzLoadGameInstance->PlayerHealth;
			CollectedCoins = BellzLoadGameInstance->CollectedCoins;
		}
	}
}

void AGladiator::OnCollectPickup()
{
	// Lets make a temp array to hold the overlapped coins
	TArray<AActor*> CollectedPickups;

	GetCapsuleComponent()->GetOverlappingActors(CollectedPickups);

	for (AActor*& TestActor : CollectedPickups)
	{
		APickupBase* Pickup = Cast<APickupBase>(TestActor);
		if (Pickup && !Pickup->IsPendingKill() && Pickup->IsActive())
		{
			/** here will be call whatever derived class (from APickupBase) overridden function, e.g. ACoinPickup::OnGetCollected()   */
			Pickup->OnGetCollected(this);
		}
	}
}

void AGladiator::AddCoins(int32 Amount)
{
	CollectedCoins += Amount;

	/** if we have a HUD widget bp  */
	if(UInGameUI* InGameUI = Cast<UInGameUI>(GameUIInstance))
	{
		/** play screen anim  */
		InGameUI->PlayCoinAnimation();
	}
}

void AGladiator::GetHUDData(float& HealthPercent, FText& CoinsText) const
{
	/** Health Percent  */
	HealthPercent = CurrentHealth / 100.f;
	
	/**  Coins  */
	CoinsText = FText::FromString(FString::Printf(TEXT("%d"), CollectedCoins));
}

void AGladiator::MoveForward(float Value)
{
	if (Controller && Value != 0.0f && IsControlable && !IsAttacking)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGladiator::MoveRight(float Value)
{
	if (Controller && Value != 0.0f && IsControlable && !IsAttacking)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGladiator::Jump()
{
	if (IsControlable && !IsAttacking)
	{
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

void AGladiator::StopJumping()
{
	if (IsControlable)
	{
		bPressedJump = false;
		JumpKeyHoldTime = 0.0f;
	}
}

void AGladiator::OnAttack()
{
	if (IsControlable)
	{
		IsAttacking = true;
	}
}

void AGladiator::OnPostAttack()
{
	IsAttacking = false;
}

void AGladiator::OnChangeWeapon()
{
	if (IsControlable)
	{
		WeaponIndex++;
		/** TODO AllWeaponsData ! */
		/*if (WeaponIndex < TablesInstance->AllWeaponsData.Num())
		{
			WeaponIndex++;
		}
		else
		{
			WeaponIndex = 1;
		}*/
	}
}

void AGladiator::TurnAtRate(float Rate)
{
	if (IsControlable)
	{
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AGladiator::LookUpAtRate(float Rate)
{
	if (IsControlable)
	{
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AGladiator::CreateHUD()
{
	if (GameUIWidget)
	{
		GameUIInstance = CreateWidget<UUserWidget>(GetWorld(), GameUIWidget);
		if (GameUIInstance)
		{
			GameUIInstance->AddToViewport();
		}
	}
}

void AGladiator::SetupGameDataTables()
{
	for (TActorIterator<AGameDataTables> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr)
		{
			TablesInstance = *ActorItr;
			TablesInstance->OnFetchAllTables();
		}
	}
}
