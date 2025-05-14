// Copyright 2019 ayumax. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class EasyJsonParserTests : ModuleRules
{
	public EasyJsonParserTests
		(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		ShadowVariableWarningLevel = WarningLevel.Warning;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"EasyJsonParser",
				"AutomationController",
				"FunctionalTesting"
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
			PrivateDependencyModuleNames.Add("EditorStyle");
		}
	}
}