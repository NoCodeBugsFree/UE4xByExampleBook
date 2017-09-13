#pragma once
#include "PowerUpObject.generated.h"

UENUM(BlueprintType)
enum class EPowerUp : uint8
{
	SPEED = 1 UMETA(DisplayName = "Speed"),
	SMASH = 2 UMETA(DisplayName = "Smash"),
	MAGNET = 3 UMETA(DisplayName = "Magnet")
};

UCLASS()
class POWERUPPLUGIN_API UPowerUpObject : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPowerUpObject();

	/** Returns the PowerUp Type  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	EPowerUp GetType() const { return PowerUpType; }
	
private:

	/** Current PowerUp Type  */
	EPowerUp PowerUpType;

};

/**
 * Creating a Plug-in with C++
 * 1) Plugins-> New Plugin-> Blank -> Name it -> Create Plugin
 * 2) "Type": "Runtime" - Runtime modules will be loaded in all cases, even in shipped
 * games. Developer modules will only be loaded in development, runtime, or
 * editor builds but never in shipping builds, and Editor modules will only be
 * loaded when the editor is starting up.
 * 3) in Build.cs add - PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "YourPluginName" });
 * 4) add new classes to corresponding target module
 */ 