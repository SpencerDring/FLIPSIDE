// Spencer Dring. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "FlipsideDiscriminatorStruct.h"
#include "UObject/NoExportTypes.h"
#include "FlipsideDiscriminatorTag.generated.h"

/**
 * 
 */
UCLASS()
class FLIPSIDEGAME_API UFlipsideDiscriminatorTag : public UObject
{
	GENERATED_BODY()

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Discriminator Settings")
	FFlipsideDiscriminatorStruct Discriminator;
	
};
