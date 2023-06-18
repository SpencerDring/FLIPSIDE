// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FLIPSIDEEditorTarget : TargetRules
{
	public FLIPSIDEEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[] { "FLIPSIDEGame", "FLIPSIDEEditor" });

		FLIPSIDEGameTarget.ApplySharedLyraTargetSettings(this);

		// This is used for touch screen development along with the "Unreal Remote 2" app
		EnablePlugins.Add("RemoteSession");
	}
}
