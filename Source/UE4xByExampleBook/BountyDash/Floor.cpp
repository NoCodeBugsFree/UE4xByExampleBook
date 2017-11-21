// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "BountyDashGameMode.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "UE4xByExampleBook.h"
#include "BountyDashGameMode.h"
#include "DestroyedFloorPiece.h"
//#include "Components/DestructibleComponent.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MyMesh(TEXT("StaticMesh'/Game/BountyDash/Meshes/DestroyableMesh.DestroyableMesh'"));
	if (MyMesh.Succeeded())
	{
		NumRepeatingMesh = 80;
		FBoxSphereBounds MeshAssetBounds = MyMesh.Object->GetBounds();
		float XBounds = MeshAssetBounds.BoxExtent.X * 2;
		float ScenePosition = ((XBounds * (NumRepeatingMesh - 1)) / 2.0f) * -1;
		KillPoint = ScenePosition - (XBounds * 0.5f);
		SpawnPoint = (ScenePosition * -1) + (XBounds * 0.5f);

		for (int i = 0; i < NumRepeatingMesh; ++i)
		{
			// Initialize Scene
			FString SceneName = "Scene" + FString::FromInt(i);
			FName SceneID = FName(*SceneName);
			USceneComponent* ThisScene = CreateDefaultSubobject<USceneComponent>(SceneID);
			check(ThisScene);
			ThisScene->SetupAttachment(RootComponent);
			ThisScene->SetRelativeLocation(FVector(ScenePosition, 0.0f, 0.0f));
			ScenePosition += XBounds;
			FloorMeshScenes.Add(ThisScene);

			// Initialize Mesh
			FString MeshName = "Mesh" + FString::FromInt(i);
			UStaticMeshComponent* ThisMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));
			check(ThisMesh);

			ThisMesh->SetupAttachment(FloorMeshScenes[i]);
			ThisMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			ThisMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

			ThisMesh->SetStaticMesh(MyMesh.Object);

			FloorMeshes.Add(ThisMesh);
		}

		CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionBox"));
		check(CollisionBox);
		CollisionBox->SetupAttachment(RootComponent);
		CollisionBox->SetBoxExtent(FVector(SpawnPoint, MeshAssetBounds.BoxExtent.Y, MeshAssetBounds.BoxExtent.Z));
		CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
	BountyDashGameMode = Cast<ABountyDashGameMode>(GetWorld()->GetAuthGameMode());
	check(BountyDashGameMode);
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/** for each of 80 scenes...  */
	for (auto Scene : FloorMeshScenes)
	{
		float XValue = 0.f;
		
		if (BountyDashGameMode)
		{
			XValue = BountyDashGameMode->GetInverseGameSpeed();
		}

		if (Scene)
		{
			Scene->AddLocalOffset(FVector(XValue, 0.0f, 0.0f));

			if (Scene->GetComponentTransform().GetLocation().X <= KillPoint && DestroyedFloorPieceTemplate)
			{
				Scene->SetRelativeLocation(FVector(SpawnPoint, 0.0f, 0.0f));

				// spawn destructible mesh and destroy
				ADestroyedFloorPiece* ThisPiece = GetWorld()->SpawnActor<ADestroyedFloorPiece>(
					DestroyedFloorPieceTemplate,
					Scene->GetComponentTransform());
				if (ThisPiece)
				{
					// ThisPiece->Destructable->ApplyDamage(100000, ThisPiece->GetActorLocation(),
						//FVector(-FMath::RandRange(-10, 10), -FMath::RandRange(-10, 10), -FMath::RandRange(-10, 10)), 10000);
				}
				/**
					Once the game has built, play the project then 
					detach the camera and navigate it to the killPoint of the floor and
					you will see destructions:
				*/
				Scene->SetRelativeLocation(FVector(SpawnPoint, 0.0f, 0.0f));
			}
		}
	}
}

