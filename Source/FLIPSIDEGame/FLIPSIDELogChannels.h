// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Logging/LogMacros.h"

class UObject;

FLIPSIDEGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogFlipside, Log, All);
FLIPSIDEGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogFlipsideExperience, Log, All);
FLIPSIDEGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogFlipsideAbilitySystem, Log, All);
FLIPSIDEGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogFlipsideTeams, Log, All);
FLIPSIDEGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogFlipsideOnline, Log, All);

FLIPSIDEGAME_API FString GetClientServerContextString(UObject* ContextObject = nullptr);
