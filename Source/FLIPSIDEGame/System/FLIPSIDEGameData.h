// Copyright Spencer Dring. All Rights Reserved.

#pragma once

#include "FlipsideDiscriminatorTag.h"
#include "Engine/DataAsset.h"

#include "FLIPSIDEGameData.generated.h"

class UGameplayEffect;
class UObject;

/**
 * UFlipsideGameData
 *
 *	Non-mutable data asset that contains global game data.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "FLIPSIDE Game Data", ShortTooltip = "Data asset containing global game data."))
class UFlipsideGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UFlipsideGameData();

	// Returns the loaded game data.
	static const UFlipsideGameData& Get();

public:

	// Gameplay effect used to apply damage.  Uses SetByCaller for the damage magnitude.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects", meta = (DisplayName = "Damage Gameplay Effect (SetByCaller)"))
	TSoftClassPtr<UGameplayEffect> DamageGameplayEffect_SetByCaller;

	// Gameplay effect used to apply healing.  Uses SetByCaller for the healing magnitude.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects", meta = (DisplayName = "Heal Gameplay Effect (SetByCaller)"))
	TSoftClassPtr<UGameplayEffect> HealGameplayEffect_SetByCaller;

	// Gameplay effect used to add and remove dynamic tags.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects")
	TSoftClassPtr<UGameplayEffect> DynamicTagGameplayEffect;

	// The publicly displayed version number. Make sure it starts with 'v'.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Versioning")
	FString PublicGameVersionString;

	// The publicly displayed build number.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Versioning")
	int32 PublicGameBuildNumber;

	// The internally displayed version number.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Versioning")
	FString PrivateGameVersionString;

	// The internally displayed build number.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Versioning")
	int32 PrivateGameBuildNumber;

	// The internally displayed game branch.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Versioning")
	FString GameBranchString;

	// The tag for this game version.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Versioning")
	UFlipsideDiscriminatorTag* DiscriminatorTag;
};
