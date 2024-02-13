
// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Netcpp : ModuleRules
{
	public Netcpp(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "Win64", "netcpp.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "Win64", "WS2_32.lib"));
	}
}
