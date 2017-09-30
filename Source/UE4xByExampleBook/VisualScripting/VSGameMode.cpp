// Fill out your copyright notice in the Description page of Project Settings.

#include "VSGameMode.h"
#include "VisualScripting/Enemy/VSEnemyCharacter.h"
#include "VisualScripting/Enemy/EnemySpawnPoint.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "VSSaveGame.h"
#include "EngineUtils.h"

void AVSGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	/** attempt to fill EnemySpawnPoints  */
	FindAndSaveAllSpawnPoints();

	/** check how many enemies we already have placed in level and store enemies amount  */
	SetPlacedEnimiesAmount();
	
	/** start spawning enemies at spawn points  */
	FTimerHandle EnemySpawnTimer;
	GetWorldTimerManager().SetTimer(EnemySpawnTimer, this, &AVSGameMode::SpawnEnemy, SpawnDelay, true);
}

void AVSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	/** if we have save game  */
	if (UGameplayStatics::DoesSaveGameExist(SaveGameSlotName, 0))
	{
		/** if we already have a save game - load it and set variables */
		if (UVSSaveGame* TestVSSaveGame = Cast<UVSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0)))
		{
			/** save reference  */
			VSSaveGame = TestVSSaveGame;

			/** get the current round from save game object  */
			CurrentRound = VSSaveGame->CurrentRound;

			/** set max enemies to spawn during this round  */
			TargetGoal = CurrentRound * RoundScaleMultiplier;

			/** if we don't want to specify enemies number 
			 *  then MaxEnemies will be equals CurrentRound
			 */
			if (!bIsMaxEnemiesNumberOverride)
			{
				MaxEnemies = CurrentRound;
			}
		}
	}
	else /** if we haven't a save game - create it */
	{
		VSSaveGame = Cast<UVSSaveGame>(UGameplayStatics::CreateSaveGameObject(UVSSaveGame::StaticClass()));
		if (VSSaveGame)
		{
			/** game starts 1st round  */
			CurrentRound = 1;

			/** save this variable to save game  */
			VSSaveGame->CurrentRound = CurrentRound;

			/** set max enemies to spawn during this round  */
			TargetGoal = CurrentRound * RoundScaleMultiplier;

			/** if we don't want to specify enemies number
			*  then MaxEnemies will be equals CurrentRound
			*/
			if (!bIsMaxEnemiesNumberOverride)
			{
				MaxEnemies = CurrentRound;
			}

			/** save game to slot  */
			UGameplayStatics::SaveGameToSlot(VSSaveGame, SaveGameSlotName, 0);
		}
	}
}

void AVSGameMode::UpdateSaveGameObject()
{
	if (VSSaveGame)
	{
		/** save this variable to save game  */
		CurrentRound = VSSaveGame->CurrentRound++;

		/** save game to slot  */
		UGameplayStatics::SaveGameToSlot(VSSaveGame, SaveGameSlotName, 0);
	}
}

void AVSGameMode::SetPlacedEnimiesAmount()
{
	TArray<AActor*> PlacedEnemies;
	if (GetWorld())
	{
		for (TActorIterator<AVSEnemyCharacter> Iter(GetWorld()); Iter; ++Iter)
		{
			if ((*Iter))
			{
				PlacedEnemies.AddUnique(*Iter);
			}
		}
	}
	CurrentEnemiesAmount = 0;
	CurrentEnemiesAmount += PlacedEnemies.Num();
}

void AVSGameMode::FindAndSaveAllSpawnPoints()
{
	if (GetWorld())
	{
		for (TActorIterator<AEnemySpawnPoint> Iter(GetWorld()); Iter; ++Iter)
		{
			if ((*Iter))
			{
				EnemySpawnPoints.AddUnique(*Iter);
			}
		}
	}

	if (EnemySpawnPoints.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode::BeginPlay() - EnemySpawnPoints.Num() < 1 . Add some EnemySpawnPoint actors to the level"));
	}
}

void AVSGameMode::SpawnEnemy()
{
	/** we have template to spawn  */
	if (EnemyCharacterToSpawnClass && CurrentEnemiesAmount < MaxEnemies)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			
			/** get random spawn point transform  */
			FVector EnemySpawnPointLocation;

			/** try to find spawn point  */
			if (EnemySpawnPoints.Num() > 1)
			{
				int32 RandomIndex = FMath::RandRange(0, EnemySpawnPoints.Num() - 1);
				if (EnemySpawnPoints.IsValidIndex(RandomIndex))
				{
					EnemySpawnPointLocation = EnemySpawnPoints[RandomIndex]->GetActorLocation();
				}

				// Get Random Point In Navigable Radius
				FNavLocation RandomPoint;
				if (GetWorld()->GetNavigationSystem()->GetRandomPointInNavigableRadius(EnemySpawnPointLocation, SpawnRadius, RandomPoint))
				{
					FVector EnemySpawnLocation = RandomPoint.Location;
					FRotator EnemySpawnRotation = FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f);
					AVSEnemyCharacter* VSEnemyCharacter = World->SpawnActor<AVSEnemyCharacter>(EnemyCharacterToSpawnClass, EnemySpawnLocation, EnemySpawnRotation, SpawnParams);
					if (VSEnemyCharacter)
					{
						CurrentEnemiesAmount++;
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(" GameMode::SpawnEnemy() failed ... EnemySpawnPoints.Num() < 1 ... Add some EnemySpawnPoint actors to the level"));
			}
		}
	}
}
