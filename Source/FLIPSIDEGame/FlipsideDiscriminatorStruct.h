// Spencer Dring. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "FlipsideDiscriminatorStruct.generated.h"

/**
 * 
 */
/** Please add a struct description */
USTRUCT(BlueprintType)
struct FFlipsideDiscriminatorStruct
{
	GENERATED_BODY()
	
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="(INTERNAL) Discriminator Name: "))
	FString INTERNALDiscriminatorName;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="(INTERNAL) Discriminator Description: "))
	FString INTERNALDiscriminatorDescription;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Discriminator Name on Widget:"))
	FString DiscriminatorNameOnWidget;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Widget Visible?", MakeStructureDefaultValue="False"))
	bool WidgetVisible;
};
