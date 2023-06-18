// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FLIPSIDEGameEOSTarget : FLIPSIDEGameTarget
{
	public FLIPSIDEGameEOSTarget(TargetInfo Target) : base(Target)
	{
		// Add override directory for EOS config files
		// We have to recompile the engine to add the custom config preprocessor definition, but that is currently not possible for installed builds
		CustomConfig = "EOS";
	}
}
