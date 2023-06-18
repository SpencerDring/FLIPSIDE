// Spencer Dring. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FlipsideGameFeatureInstance.generated.h"

/**
 * 
 */
UCLASS()
class FLIPSIDEGAME_API UFlipsideGameFeatureInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void EnableFlipsideGameFeature(FString FeaturePluginName);
	
};
