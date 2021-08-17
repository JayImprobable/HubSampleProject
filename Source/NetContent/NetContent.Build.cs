// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NetContent : ModuleRules
{
	public NetContent(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
