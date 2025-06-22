// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EasyJsonParserV2Tests : ModuleRules
{
	public EasyJsonParserV2Tests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		CppStandard = CppStandardVersion.Latest;
		bEnableExceptions = true;
		
		PublicIncludePaths.AddRange(
			new string[] {
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"EasyJsonParser",
				"EasyJsonParserV2"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Json",
				"FunctionalTesting",
				"AutomationController"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}