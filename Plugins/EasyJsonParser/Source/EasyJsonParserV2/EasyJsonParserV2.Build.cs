// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EasyJsonParserV2 : ModuleRules
{
	public EasyJsonParserV2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// Latest C++ features for better optimization
		CppStandard = CppStandardVersion.Latest;
		
		// Enable exceptions for proper error handling
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
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Json"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}