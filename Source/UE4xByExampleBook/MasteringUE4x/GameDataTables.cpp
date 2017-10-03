// Fill out your copyright notice in the Description page of Project Settings.

#include "GameDataTables.h"
#include "Components/BillboardComponent.h"

// Sets default values
AGameDataTables::AGameDataTables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	BillboardComponent->SetupAttachment(RootComponent);
	BillboardComponent->SetWorldScale3D(FVector(10.f, 10.f, 10.f));
}

void AGameDataTables::OnFetchAllTables()
{
	if (!WeaponsTable && !MissionsTable)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponsTable == NULL OR MissionsTable == NULL"));
		return;
	}

	/** read all datatable data to array  */
	FString ContextString;
	// TArray<FName> RowNames;
	RowNames = WeaponsTable->GetRowNames();
	
	/** fill the AllWeaponsData array */
	for (auto& name : RowNames)
	{
		FWeaponStruct* RowFromArray = WeaponsTable->FindRow<FWeaponStruct>(name, ContextString);
		if (RowFromArray)
		{
			AllWeaponsData.Add(*RowFromArray);
		}
	}
	
	RowNames = MissionsTable->GetRowNames();

	/** fill the AllMissionsData array */
	for (auto& name : RowNames)
	{
		FMissionStruct* RowFromArray = MissionsTable->FindRow<FMissionStruct>(name, ContextString);
		if (RowFromArray)
		{
			AllMissionsData.Add(*RowFromArray);
		}
	}
}
 
//void AGameDataTables::OnFetchAllTables()
//{
//	/** Any will be okay, not necessarily to be this cell name  */
//	static const FString ContextString(TEXT("Name"));
//
//	/** Get all the row names and store them temporary here, the point is
//	to define the amount of rows, the best way yet!  */
//	TArray<FName> WeaponsTableRowsNames = WeaponsTable->GetRowNames();
//
//	/** usually we used 0 as the start index, but a table have it' first
//	row indexed as 1, other wise it will crash  */
//	for (int32 i = 1; i < WeaponsTableRowsNames.Num() + 1; i++)
//	{
//		FString IndexString = FString::FromInt((int32)i);
//		FName IndexName = FName(*IndexString);
//
//		/** fill the weapon data array  */
//		FWeaponStruct* aStructRow = WeaponsTable->FindRow<FWeaponStruct>(IndexName, ContextString, true);
//		AllWeaponsData.Add(*aStructRow);
//	}
//
//	/** Get all the row names and store them temporary here, the point is to define the amount of rows, the best way yet! */
//	TArray<FName> MissionsTableRowsNames = MissionsTable->GetRowNames();
//
//	/** usually we used 0 as the start index, but a table have it' first row indexed as 1, other wise it will crash  */
//	for (int32 e = 1; e < MissionsTableRowsNames.Num() + 1; e++)
//	{
//		FString IndexString = FString::FromInt((int32)e);
//		FName IndexName = FName(*IndexString);
//
//		/**  fill the mission data array   */
//		FMissionStruct* aStructRow = MissionsTable->FindRow<FMissionStruct>(IndexName, ContextString, true);
//		AllMissionsData.Add(*aStructRow);
//	}
//}


//void AGameDataTables::OnFetchAllTables()
//{
//	/** Any will be okay, not necessarily to be this cell name  */
//	static const FString ContextString(TEXT("Name"));
//
//	/** Get all the row names and store them temporary here, the point is
//	to define the amount of rows, the best way yet!  */
//	TArray<FName> WeaponsTableRowsNames = WeaponsTable->GetRowNames();
//
//	/** usually we used 0 as the start index, but a table have it' first
//	row indexed as 1, other wise it will crash  */
//	for (int32 i = 1; i < WeaponsTableRowsNames.Num() + 1; i++)
//	{
//		FString IndexString = FString::FromInt((int32)i);
//		FName IndexName = FName(*IndexString);
//
//		/** fill the weapon data array  */
//		FWeaponStruct* aStructRow = WeaponsTable->FindRow<FWeaponStruct>(IndexName, ContextString, true);
//		AllWeaponsData.Add(*aStructRow);
//	}
//
//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(AllWeaponsData.Num()));
//
//	/** Just a print to screen to check if I got all the values correctly!  */
//	for (int32 c = 0; c < AllWeaponsData.Num(); c++)
//	{
//		FString message = TEXT(" Number: ") + FString::FromInt(c) + TEXT(" Name: ") + AllWeaponsData[c].DisplayName + TEXT(" Icon: ")
//			+ AllWeaponsData[c].Icon + TEXT(" Damage: ")
//			+ FString::FromInt(AllWeaponsData[c].Damage) + TEXT(" Cooldown: ")
//			+ FString::FromInt(AllWeaponsData[c].CooldownTime);
//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, message);
//	}
//	 
//	/** Get all the row names and store them temporary here, the point is to define the amount of rows, the best way yet! */
//	TArray<FName> MissionsTableRowsNames = MissionsTable->GetRowNames();
//
//	/** usually we used 0 as the start index, but a table have it' first row indexed as 1, other wise it will crash  */
//	for (int32 e = 1; e < MissionsTableRowsNames.Num() + 1; e++)
//	{
//		FString IndexString = FString::FromInt((int32)e);
//		FName IndexName = FName(*IndexString);
//
//		/**  fill the mission data array   */
//		FMissionStruct* aStructRow = MissionsTable->FindRow<FMissionStruct>(IndexName, ContextString, true);
//		AllMissionsData.Add(*aStructRow);
//	}
//
//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(AllMissionsData.Num()));
//
//	// Just a print to screen to check if I got all the values correctly!
//	for (int32 x = 0; x < AllMissionsData.Num(); x++)
//	{
//		FString message = TEXT(" Number: ") + FString::FromInt(x) + TEXT("Kills: ")
//			+ FString::FromInt(AllMissionsData[x].Kill)
//			+ TEXT("Collects : ") 
//			+ FString::FromInt(AllMissionsData[x].Collect);
//			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, message);
//	}
//}




