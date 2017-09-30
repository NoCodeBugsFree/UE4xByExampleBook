// Fill out your copyright notice in the Description page of Project Settings.

#include "NSGameMode.h"
#include "NSCharacter.h"
#include "ConstructorHelpers.h"
#include "NSSpawnPoint.h"
#include "NSPlayerState.h"
#include "NSHUD.h"
#include "NSGameState.h"
#include "EngineUtils.h"

/** This bool has been declared as static so that its state
	will persist through server travels to new maps.  
*/
bool ANSGameMode::bInGameMenu = true;

ANSGameMode::ANSGameMode()
{
	/** set Pawn_BP  */
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn_BP_Class(TEXT("/Game/NetWorkShooter/BP/BP_NSCharacter"));
	if (PlayerPawn_BP_Class.Class != NULL)
	{
		DefaultPawnClass = PlayerPawn_BP_Class.Class;
	}

	/** set HUD_BP  */
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUD_BP_Class(TEXT("/Game/NetWorkShooter/BP/BP_NSHUD"));
	if (PlayerHUD_BP_Class.Class != NULL)
	{
		HUDClass = PlayerHUD_BP_Class.Class;
	}
	
	/**  set PlayerState_BP */
	static ConstructorHelpers::FClassFinder<APlayerState> PlayerState_BP_Class(TEXT("/Game/NetWorkShooter/BP/BP_NSPlayerState"));
	if (PlayerState_BP_Class.Class != NULL)
	{
		PlayerStateClass = PlayerState_BP_Class.Class;
	}

	/**  set GameState_BP */
	static ConstructorHelpers::FClassFinder<AGameState> GameState_BP_Class(TEXT("/Game/NetWorkShooter/BP/BP_NSGameState"));
	if (GameState_BP_Class.Class != NULL)
	{
		GameStateClass = GameState_BP_Class.Class;
	}
	
	bReplicates = true;
}

void ANSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		/** set  bInGameMenu state in Game State */
		if (ANSGameState* NSGameState = Cast<ANSGameState>(GameState))
		{
			NSGameState->SetIsInMenu(bInGameMenu);
		}


		for (TActorIterator<ANSSpawnPoint> Iter(GetWorld()); Iter; ++Iter)
		{
			if ((*Iter)->GetTeam() == ETeam::RED_TEAM)
			{
				RedSpawns.Add(*Iter);
			}
			else
			{
				BlueSpawns.Add(*Iter);
			}
		}

		// Spawn the server
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			if (ANSCharacter* NSCharacter = Cast<ANSCharacter>(PlayerController->GetPawn()))
			{
				NSCharacter->SetTeam(ETeam::BLUE_TEAM);
				BlueTeam.Add(NSCharacter);
				Spawn(NSCharacter);
			}
		}
	}
}

void ANSGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Role == ROLE_Authority)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		/**  
			If so, we iterate over all characters
			to be spawned and invoke the Spawn() function. This will ensure that any characters
			that need to spawn that round will do so. We are doing this check in the tick to
			ensure that any spawns rejected due to blocked spawn points will still be spawned eventually.   
		*/
		if (ToBeSpawned.Num() != 0)
		{
			for (auto CharacterToSpawn : ToBeSpawned)
			{
				Spawn(CharacterToSpawn);
			}
		}

		/** that the player controller we obtained is valid and that
			the server player has pressed the R key  */
		if (PlayerController && PlayerController->IsInputKeyDown(EKeys::R))
		{
			bInGameMenu = false;
			
			/** 
				This method will travel the
				server to the provided map URL; it will also travel all connected clients to the map.
				You may have noticed that we have appended the map URL with ?Listen . This is
				an extra command that ensures that the map the server is traveling to will accept
				connecting clients.
				The important thing to note is that, when the server travels the player states, player
				controllers and game states all persist through traveling.
			*/
			GetWorld()->ServerTravel(L"/Game/BossMode/Maps/BoseModeMap?Listen");
			
			/** set  bInGameMenu state in Game State */
			if (ANSGameState* NSGameState = Cast<ANSGameState>(GameState))
			{
				NSGameState->SetIsInMenu(bInGameMenu);
			}
		}
	}
}

void ANSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ANSCharacter* TeamlessCharacter = Cast<ANSCharacter>(NewPlayer->GetPawn()); 
	
	ANSPlayerState* NPlayerState = Cast<ANSPlayerState>(NewPlayer->PlayerState);

	/** set player's state  */
	if (TeamlessCharacter && NPlayerState)
	{
		TeamlessCharacter->SetNSPlayerState(NPlayerState);
	}

	// Assign Team and spawn
	if (Role == ROLE_Authority && TeamlessCharacter)
	{
		if (BlueTeam.Num() > RedTeam.Num())
		{
			RedTeam.Add(TeamlessCharacter);

			NPlayerState->SetTeam(ETeam::RED_TEAM);
		}
		else if (BlueTeam.Num() < RedTeam.Num())
		{
			BlueTeam.Add(TeamlessCharacter);

			NPlayerState->SetTeam(ETeam::BLUE_TEAM);
		}
		else // Teams are equal
		{
			BlueTeam.Add(TeamlessCharacter);

			NPlayerState->SetTeam(ETeam::BLUE_TEAM);
		}

		/** set current team from Player State  */
		TeamlessCharacter->CurrentTeam = NPlayerState->GetTeam();

		/** set the player color accordingly to team  */
		TeamlessCharacter->SetTeam(NPlayerState->GetTeam());

		/** spawn our character  */
		Spawn(TeamlessCharacter);
	}
}

void ANSGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		bInGameMenu = true;
	}
}

void ANSGameMode::Respawn(class ANSCharacter* CharacterToRespawn)
{
	if (Role == ROLE_Authority && CharacterToRespawn)
	{
		AController* Controller = CharacterToRespawn->GetController();

		/**  This will detach the old character pawn from the player controller, 
			this will flag that old pawn for destroy and free up the controller for a new character.
			This will also occur on the client, so be warned, if for some reason the new character
			is not spawned and assigned to the controller, the client will be left characterless 
		*/
		CharacterToRespawn->DetachFromControllerPendingDestroy();

		/** Spawn new character  */
		ANSCharacter* NewNSCharacter = Cast<ANSCharacter>(GetWorld()->SpawnActor(DefaultPawnClass));

		if (NewNSCharacter)
		{
			/** Posses new Character */
			Controller->Possess(NewNSCharacter);

			ANSPlayerState* NSPlayerState = Cast<ANSPlayerState>(NewNSCharacter->GetController()->PlayerState);
			if (NSPlayerState)
			{
				NewNSCharacter->CurrentTeam = NSPlayerState->GetTeam();

				NewNSCharacter->SetNSPlayerState(NSPlayerState);

				/** so that it is positioned properly  */
				Spawn(NewNSCharacter);

				/** the mesh materials are colored properly  */
				NewNSCharacter->SetTeam(NewNSCharacter->GetNSPlayerState()->GetTeam());
			}
		}
	}
}

void ANSGameMode::Spawn(class ANSCharacter* Character)
{
	if (Role == ROLE_Authority && Character)
	{
		// Find Spawn point that is not blocked
		ANSSpawnPoint* CurrentSpawnPoint = nullptr;

		/** The pointer to target team array spawn points  */
		TArray<ANSSpawnPoint*>* TargetTeam = nullptr;

		if (Character->CurrentTeam == ETeam::BLUE_TEAM)
		{
			/** The pointer to target team array is set to address of BlueSpawns array  */
			TargetTeam = &BlueSpawns;
		}
		else
		{
			/** The pointer to target team array is set to address of RedSpawns array  */
			TargetTeam = &RedSpawns;
		}

		/** We then iterate over that array and check whether the spawn is not blocked. If
			we find a non-blocked spawn, we check whether the player is contained within the
			ToBeSpawned array. If so, we remove from the array before spawning, as this means
			it was blocked from spawning at the last attempt.  
		*/
		for (auto Spawn : (*TargetTeam))
		{
			if (!Spawn->GetBlocked())
			{
				// Remove from spawn queue location
				if (ToBeSpawned.Find(Character) != INDEX_NONE)
				{
					ToBeSpawned.Remove(Character);
				}

				/** The act of spawning is very simple, as the character will have already been created
					in memory when the client joined; we simply set the actor location to be that of the
					spawn point. We then update the overlaps on the spawn to ensure it detects the new
					actor. We then return out of the function to cease any further execution.  
				*/
				Character->SetActorLocation(Spawn->GetActorLocation());
				Spawn->UpdateOverlaps();

				/** get out because success  */
				return;
			}
		}

		/** If the function continues, this means the player was not spawned and should be
			added to the ToBeSpawned array. We check that the player does not already exist
			in the array and add it.
		*/
		if (ToBeSpawned.Find(Character) == INDEX_NONE)
		{
			/** if we have not this one in our array - add it  */
			ToBeSpawned.Add(Character);
		}
	}
}

