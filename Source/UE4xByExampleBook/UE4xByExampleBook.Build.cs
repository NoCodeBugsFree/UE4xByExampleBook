// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UE4xByExampleBook : ModuleRules
{
	public UE4xByExampleBook(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PowerUpPlugin", "AIModule", "GameplayTasks", "Paper2D", "UMG", "AssetTools", "MainFrame", "AppFramework", "Landscape", "LandscapeEditor", "HTTP" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Paper2D", "Slate", "SlateCore", "UMG" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
