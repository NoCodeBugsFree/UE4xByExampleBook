// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleCharacter.h"
#include "Camera/CameraComponent.h"
#include "InventoryComponent.h"
#include "InventoryActor.h"

// Sets default values
ASimpleCharacter::ASimpleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a CameraComponent
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComponent->SetupAttachment(RootComponent);

	/** allow mouse up/down  */
	bUseControllerRotationPitch = true;

	MyInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");
}

// Called when the game starts or when spawned
void ASimpleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASimpleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/**  Jump */
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/** Movement */
	PlayerInputComponent->BindAxis("MoveForward", this, &ASimpleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASimpleCharacter::MoveRight);

	/**  Turn and LookUp */
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	/** Drop Item  */
	InputComponent->BindAction("DropItem", IE_Pressed, this, &ASimpleCharacter::DropItem);
}

void ASimpleCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Other && Other != this && !IsPendingKill())
	{
		AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);

		if (InventoryItem)
		{
			TakeItem(InventoryItem);
		}
	}
}

void ASimpleCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASimpleCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}


void ASimpleCharacter::DropItem()
{
	if (MyInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	AInventoryActor* Item = MyInventory-> CurrentInventory.Last();
	MyInventory->RemoveFromInventory(Item);
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax() * 4);

	Item->PutDown(PutDownLocation);
}

void ASimpleCharacter::TakeItem(AInventoryActor* InventoryItem)
{
	if (InventoryItem)
	{
		InventoryItem->PickUp();
		MyInventory->AddToInventory(InventoryItem);
	}
}
