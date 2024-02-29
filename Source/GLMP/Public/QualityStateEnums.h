#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EQualityLevelState : uint8
{
	Low,
	Medium,
	High,
	Epic,
	Cinematic
};
ENUM_RANGE_BY_COUNT(EQualityLevelState, EQualityLevelState::Cinematic)


UENUM(BlueprintType)
enum class EQualityTypeState : uint8
{
	ResolutionScale		UMETA(DisplayName = "Resolution Scale"),
	ViewDistance		UMETA(DisplayName = "View Distance"),
	AntiAliasing		UMETA(DisplayName = "Anti-Aliasing"),
	PostProcessing		UMETA(DisplayName = "Post Processing"),
	Shadows				UMETA(DisplayName = "Shadows"),
	GlobalIllumination	UMETA(DisplayName = "Global Illumination"),
	Reflection			UMETA(DisplayName = "Reflection"),
	Textures			UMETA(DisplayName = "Textures"),
	Effects				UMETA(DisplayName = "Effects"),
	Foliage				UMETA(DisplayName = "Foliage")
};
ENUM_RANGE_BY_COUNT(EQualityTypeState, EQualityTypeState::Foliage)


template<typename T>
FString EnumToString(const FString& enumName, const T value)
{
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName, true);
	return pEnum ? pEnum->GetValueAsString(value) : FString();
}
