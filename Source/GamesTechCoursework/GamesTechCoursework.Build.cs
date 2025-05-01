// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamesTechCoursework : ModuleRules
{
	public GamesTechCoursework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"EnhancedInput",
			"UMG",
			"NavigationSystem",
			"AIModule",
			"GameplayTasks",
			"Niagara"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"SQLiteCore",
			"SQLiteSupport", 
		});
	}
}
