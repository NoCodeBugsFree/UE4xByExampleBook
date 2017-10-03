// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameDataTables.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FWeaponStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Icon = "None";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString DisplayName = "None";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Damage = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CooldownTime = 0;

	// default constructor
	FWeaponStruct()
	{
		Icon = "None";
		DisplayName = "None";
		Damage = 0;
		CooldownTime = 0;
	}
};


USTRUCT(Blueprintable)
struct FMissionStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Kill = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Collect = 0;

	// default constructor
	FMissionStruct()
	{
		Kill = 0;
		Collect = 0;
	}
};

UCLASS()
class UE4XBYEXAMPLEBOOK_API AGameDataTables : public AActor
{
	GENERATED_BODY()
	
	/* Billboard Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* BillboardComponent;
	
public:	
	
	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameDataTables")
	UDataTable* WeaponsTable;

	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameDataTables")
	UDataTable* MissionsTable;

	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameDataTables")
	TArray<FWeaponStruct>AllWeaponsData;

	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameDataTables")
	TArray<FMissionStruct>AllMissionsData;

	/**   */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameDataTables")
	TArray<FName> RowNames;
	
	/**   */
	UFUNCTION(BlueprintCallable, Category = "Game DataTables")
	void OnFetchAllTables();

protected:

	// Sets default values for this actor's properties
	AGameDataTables();
};
