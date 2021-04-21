// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class FreeRunners : ModuleRules
{
	private string ProjectRoot { get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../")); } }
	private string ThirdPartyPath { get { return Path.GetFullPath(Path.Combine(ModuleDirectory, ProjectRoot, "ThirdParty")); } }

	public FreeRunners(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		LoadMiniUPnP(Target);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}

	public bool LoadMiniUPnP(ReadOnlyTargetRules Target) {
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64)) {
			isLibrarySupported = true;
			PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "MiniUPnP", "lib", "win64", "miniupnpc.lib"));
		} else if ((Target.Platform == UnrealTargetPlatform.Win32)) {
			isLibrarySupported = true;
			PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "MiniUPnP", "lib", "win32", "miniupnpc.lib"));
		} else {
			System.Console.WriteLine("Unhandled platform when loading MiniUPnP\n");
		}

		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "MiniUPnP", "include"));

		//RuntimeDependencies.Add(Path.Combine("$(EngineDir)", "Binaries", "ThirdParty", "MiniUPnP", "win64/miniupnpc.dll"));
		//PublicDelayLoadDLLs.Add("miniupnpc.dll");
		//PublicDefinitions.Add("");
		return isLibrarySupported;
	}
}
