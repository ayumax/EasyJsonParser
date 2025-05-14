// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class EasyJsonParserTestEditorTarget : TargetRules
{
	public EasyJsonParserTestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		CppStandard = CppStandardVersion.Latest;

		ExtraModuleNames.Add("EasyJsonParserTest");
	}
}
