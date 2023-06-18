// Copyright Epic Games, Inc. All Rights Reserved.

#include "FLIPSIDEGameData.h"
#include "FLIPSIDEAssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FLIPSIDEGameData)

UFlipsideGameData::UFlipsideGameData()
{
}

const UFlipsideGameData& UFlipsideGameData::UFlipsideGameData::Get()
{
	return UFlipsideAssetManager::Get().GetGameData();
}
