// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WOS : ModuleRules
{
    public WOS(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp20;

        bUseUnity = false;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "EnhancedInput", "Paper2D", "Slate", "SlateCore", "DatabaseSupport", "SQLiteCore", "SQLiteSupport" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Netcpp", "UnrealEd", "ComponentVisualizers" });

        PublicIncludePaths.AddRange(new string[]
        {
            "WOS/",
            "WOS/Network"
        });
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
