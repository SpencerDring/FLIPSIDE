// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class FLIPSIDEServerTarget : TargetRules
{
	public FLIPSIDEServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[] { "FLIPSIDEGame" });

		FLIPSIDEGameTarget.ApplySharedLyraTargetSettings(this);

		bUseChecksInShipping = true;
	}
}
