// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "BountyDashGameMode.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "UE4xByExampleBook.h"
#include "BountyDashGameMode.h"
#include "DestroyedFloorPiece.h"
#include "Components/DestructibleComponent.h"

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
		FBoxSphereBounds myBounds = MyMesh.Object->GetBounds();
		float XBounds = myBounds.BoxExtent.X * 2;
		float ScenePos = ((XBounds * (NumRepeatingMesh - 1)) / 2.0f) * -1;
		KillPoint = ScenePos - (XBounds * 0.5f);
		SpawnPoint = (ScenePos * -1) + (XBounds * 0.5f);

		for (int i = 0; i < NumRepeatingMesh; ++i)
		{
			// Initialize Scene
			FString SceneName = "Scene" + FString::FromInt(i);
			FName SceneID = FName(*SceneName);
			USceneComponent* thisScene = CreateDefaultSubobject<USceneComponent>(SceneID);
			check(thisScene);
			thisScene->SetupAttachment(RootComponent);
			thisScene->SetRelativeLocation(FVector(ScenePos, 0.0f, 0.0f));
			ScenePos += XBounds;
			FloorMeshScenes.Add(thisScene);

			// Initialize Mesh
			FString MeshName = "Mesh" + FString::FromInt(i);
			UStaticMeshComponent* thisMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*MeshName));
			check(thisMesh);

			thisMesh->SetupAttachment(FloorMeshScenes[i]);
			thisMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			thisMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

			thisMesh->SetStaticMesh(MyMesh.Object);

			FloorMeshes.Add(thisMesh);
		}

		CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionBox"));
		check(CollisionBox);
		CollisionBox->SetupAttachment(RootComponent);
		CollisionBox->SetBoxExtent(FVector(SpawnPoint, myBounds.BoxExtent.Y, myBounds.BoxExtent.Z));
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

	for (auto Scene : FloorMeshScenes)
	{
		float XValue = 0.f;
		
		if (BountyDashGameMode)
		{
			XValue = BountyDashGameMode->GetInvGameSpeed();
		}

		if (Scene)
		{
			Scene->AddLocalOffset(FVector(XValue, 0.0f, 0.0f));

			if (Scene->GetComponentTransform().GetLocation().X <= KillPoint)
			{
				Scene->SetRelativeLocation(FVector(SpawnPoint, 0.0f, 0.0f));

				// spawn destructible mesh and destroy
				ADestroyedFloorPiece* thisPiece = GetWorld()->SpawnActor<ADestroyedFloorPiece>(
					ADestroyedFloorPiece::StaticClass(),
					Scene->GetComponentTransform());
				if (thisPiece)
				{
					thisPiece->Destructable->ApplyDamage(100000, thisPiece->GetActorLocation(),
						FVector(-FMath::RandRange(-10, 10), -FMath::RandRange(-10, 10), -FMath::RandRange(-10, 10)), 10000);
				}
				Scene->SetRelativeLocation(FVector(SpawnPoint, 0.0f, 0.0f));
			}
		}
	}
}

float AFloor::GetKillPoint()
{
	return KillPoint;
}

float AFloor::GetSpawnPoint()
{
	return SpawnPoint;
}

