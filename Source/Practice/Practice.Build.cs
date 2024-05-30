// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Practice : ModuleRules
{
	public Practice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
    // UMG Depencies
    PublicDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore"});

    // Niagara Depencies
    PublicDependencyModuleNames.AddRange(new string[] { "Niagara" });
  }
}
