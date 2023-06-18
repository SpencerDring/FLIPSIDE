// Spencer Dring. All rights reserved.


#include "FlipsideGameFeatureInstance.h"

#include "FLIPSIDELogChannels.h"
#include "GameFeaturesSubsystem.h"

void UFlipsideGameFeatureInstance::EnableFlipsideGameFeature(FString FeaturePluginName)
{
		FString PluginURL = "";

		UGameFeaturesSubsystem::Get().GetPluginURLByName(FeaturePluginName, PluginURL);
		UE_LOG(LogFlipside, Log, TEXT("Got game feature URL: %s"), *PluginURL);
		UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(PluginURL, FGameFeaturePluginLoadComplete());
		UE_LOG(LogFlipside, Log, TEXT("Enabled game feature: %s"), *FeaturePluginName);
}
