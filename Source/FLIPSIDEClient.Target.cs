// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FLIPSIDEClientTarget : TargetRules
{
	public FLIPSIDEClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[] { "FLIPSIDEGame" });

		FLIPSIDEGameTarget.ApplySharedLyraTargetSettings(this);
	}
}
