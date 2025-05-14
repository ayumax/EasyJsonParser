// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EasyJsonParser : ModuleRules
{
	public EasyJsonParser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
		bEnableExceptions = true;

		PublicDependencyModuleNames.Add("Core");
		
		PrivateDependencyModuleNames.AddRange([
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"Json"
		]);
	}
}
