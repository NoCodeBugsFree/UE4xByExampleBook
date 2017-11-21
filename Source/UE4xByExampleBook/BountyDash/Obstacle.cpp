// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"
#include "Components/SphereComponent.h"
#include "BountyDashGameMode.h"
//#include "Components/DestructibleComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Mesh"));
	check(DestructibleMesh);
	DestructibleMesh->SetupAttachment(Collider);
	DestructibleMesh->SetCollisionResponseToAllChannels(ECR_Ignore);*/
}

void AObstacle::MyOnActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}

void AObstacle::MyOnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}


