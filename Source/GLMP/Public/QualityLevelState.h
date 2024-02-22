#pragma once

#include "CoreMinimal.h"
#include "QualityLevelState.generated.h"

UENUM(BlueprintType)
enum class EQualityLevelState : uint8
{
	Low,
	Medium,
	High,
	Epic,
	Cinematic
};

