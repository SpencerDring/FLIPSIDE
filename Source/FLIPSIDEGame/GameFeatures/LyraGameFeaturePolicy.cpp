// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFeatures/LyraGameFeaturePolicy.h"

#include "FLIPSIDELogChannels.h"
#include "AbilitySystem/LyraGameplayCueManager.h"
#include "GameFeatureData.h"
#include "GameplayCueSet.h"

ULyraGameFeaturePolicy::ULyraGameFeaturePolicy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ULyraGameFeaturePolicy& ULyraGameFeaturePolicy::Get()
{
	return UGameFeaturesSubsystem::Get().GetPolicy<ULyraGameFeaturePolicy>();
}

void ULyraGameFeaturePolicy::InitGameFeatureManager()
{
	Observers.Add(NewObject<ULyraGameFeature_HotfixManager>());
	Observers.Add(NewObject<ULyraGameFeature_AddGameplayCuePaths>());

	UGameFeaturesSubsystem& Subsystem = UGameFeaturesSubsystem::Get();
	for (UObject* Observer : Observers)
	{
		Subsystem.AddObserver(Observer);
	}

	//Check for flipside versioning tag in plugin files.
	FString ProjectVersionString = "";
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersionString,
		GGameIni
		);

	FString ProjectMajorVersionString = "", ProjectMinorVersionString = "";
	ProjectVersionString.Split(".", &ProjectMajorVersionString, &ProjectMinorVersionString);

	ProjectMajorVersion = FCString::Atoi(*ProjectMajorVersionString);
	ProjectMinorVersion = FCString::Atoi(*ProjectMinorVersionString);

	auto AdditionalFilter = [&](const FString& PluginFilename, const FGameFeaturePluginDetails& PluginDetails, FBuiltInGameFeaturePluginBehaviorOptions& outOptions) -> bool
	{
		UE_LOG (LogFlipside, Log, TEXT("%s"), *PluginFilename);
		const FString* Version = PluginDetails.AdditionalMetadata.Find("MinimumAllowedFlipsideVersion");

		if(Version && !Version->IsEmpty())
		{
			FString RequiredMajorVersionString = "", RequiredMinorVersionString = "";
			Version->Split(".", &RequiredMajorVersionString, &RequiredMinorVersionString);
			int32 RequiredMajorVersion = FCString::Atoi(*RequiredMajorVersionString);
			int32 RequiredMinorVersion = FCString::Atoi(*RequiredMinorVersionString);

			bool Result = ProjectMajorVersion > RequiredMajorVersion || (ProjectMajorVersion == RequiredMajorVersion && ProjectMinorVersion >= RequiredMinorVersion);
			UE_LOG(LogFlipside, Log, TEXT("%s: %s | Required Flipside Version: %d.%d"), *PluginFilename, Result ? TEXT("Loaded") : TEXT("Ignored"), RequiredMajorVersion, RequiredMinorVersion);
			return Result;
		}
		
		return true;
	};

	UE_LOG(LogFlipside, Log, TEXT("Scanning for game feature plugins for Flipside version: %s"), *ProjectVersionString);
	UGameFeaturesSubsystem::Get().LoadBuiltInGameFeaturePlugins(AdditionalFilter);

	Super::InitGameFeatureManager();
}

void ULyraGameFeaturePolicy::ShutdownGameFeatureManager()
{
	Super::ShutdownGameFeatureManager();

	UGameFeaturesSubsystem& Subsystem = UGameFeaturesSubsystem::Get();
	for (UObject* Observer : Observers)
	{
		Subsystem.RemoveObserver(Observer);
	}
	Observers.Empty();
}

TArray<FPrimaryAssetId> ULyraGameFeaturePolicy::GetPreloadAssetListForGameFeature(const UGameFeatureData* GameFeatureToLoad, bool bIncludeLoadedAssets) const
{
	return Super::GetPreloadAssetListForGameFeature(GameFeatureToLoad, bIncludeLoadedAssets);
}

const TArray<FName> ULyraGameFeaturePolicy::GetPreloadBundleStateForGameFeature() const
{
	return Super::GetPreloadBundleStateForGameFeature();
}

void ULyraGameFeaturePolicy::GetGameFeatureLoadingMode(bool& bLoadClientData, bool& bLoadServerData) const
{
	// Editor will load both, this can cause hitching as the bundles are set to not preload in editor
	bLoadClientData = !IsRunningDedicatedServer();
	bLoadServerData = !IsRunningClientOnly();
}

bool ULyraGameFeaturePolicy::IsPluginAllowed(const FString& PluginURL) const
{
	return Super::IsPluginAllowed(PluginURL);
}

//////////////////////////////////////////////////////////////////////
//

#include "Hotfix/LyraHotfixManager.h"

void ULyraGameFeature_HotfixManager::OnGameFeatureLoading(const UGameFeatureData* GameFeatureData, const FString& PluginURL)
{
	if (ULyraHotfixManager* HotfixManager = Cast<ULyraHotfixManager>(UOnlineHotfixManager::Get(nullptr)))
	{
		HotfixManager->RequestPatchAssetsFromIniFiles();
	}
}

//////////////////////////////////////////////////////////////////////
//

#include "AbilitySystemGlobals.h"
#include "GameFeatureAction_AddGameplayCuePath.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraGameFeaturePolicy)

class FName;
struct FPrimaryAssetId;

void ULyraGameFeature_AddGameplayCuePaths::OnGameFeatureRegistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ULyraGameFeature_AddGameplayCuePaths::OnGameFeatureRegistering);
	
	const FString PluginRootPath = TEXT("/") + PluginName;
	for (const UGameFeatureAction* Action : GameFeatureData->GetActions())
	{
		if (const UGameFeatureAction_AddGameplayCuePath* AddGameplayCueGFA = Cast<UGameFeatureAction_AddGameplayCuePath>(Action))
		{
			const TArray<FDirectoryPath>& DirsToAdd = AddGameplayCueGFA->GetDirectoryPathsToAdd();
			
			if (ULyraGameplayCueManager* GCM = ULyraGameplayCueManager::Get())
			{
				UGameplayCueSet* RuntimeGameplayCueSet = GCM->GetRuntimeCueSet();
				const int32 PreInitializeNumCues = RuntimeGameplayCueSet ? RuntimeGameplayCueSet->GameplayCueData.Num() : 0;

				for (const FDirectoryPath& Directory : DirsToAdd)
				{
					FString MutablePath = Directory.Path;
					UGameFeaturesSubsystem::FixPluginPackagePath(MutablePath, PluginRootPath, false);
					GCM->AddGameplayCueNotifyPath(MutablePath, /** bShouldRescanCueAssets = */ false);	
				}
				
				// Rebuild the runtime library with these new paths
				if (!DirsToAdd.IsEmpty())
				{
					GCM->InitializeRuntimeObjectLibrary();	
				}

				const int32 PostInitializeNumCues = RuntimeGameplayCueSet ? RuntimeGameplayCueSet->GameplayCueData.Num() : 0;
				if (PreInitializeNumCues != PostInitializeNumCues)
				{
					GCM->RefreshGameplayCuePrimaryAsset();
				}
			}
		}
	}
}

void ULyraGameFeature_AddGameplayCuePaths::OnGameFeatureUnregistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)
{
	const FString PluginRootPath = TEXT("/") + PluginName;
	for (const UGameFeatureAction* Action : GameFeatureData->GetActions())
	{
		if (const UGameFeatureAction_AddGameplayCuePath* AddGameplayCueGFA = Cast<UGameFeatureAction_AddGameplayCuePath>(GameFeatureData))
		{
			const TArray<FDirectoryPath>& DirsToAdd = AddGameplayCueGFA->GetDirectoryPathsToAdd();
			
			if (UGameplayCueManager* GCM = UAbilitySystemGlobals::Get().GetGameplayCueManager())
			{
				int32 NumRemoved = 0;
				for (const FDirectoryPath& Directory : DirsToAdd)
				{
					FString MutablePath = Directory.Path;
					UGameFeaturesSubsystem::FixPluginPackagePath(MutablePath, PluginRootPath, false);
					NumRemoved += GCM->RemoveGameplayCueNotifyPath(MutablePath, /** bShouldRescanCueAssets = */ false);
				}

				ensure(NumRemoved == DirsToAdd.Num());
				
				// Rebuild the runtime library only if there is a need to
				if (NumRemoved > 0)
				{
					GCM->InitializeRuntimeObjectLibrary();	
				}			
			}
	}
	}
}
