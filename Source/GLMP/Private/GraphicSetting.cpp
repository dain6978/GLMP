// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicSetting.h"

#include "Components/ComboBoxString.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"


void UGraphicSetting::NativePreConstruct()
{
	if (ComboBox_Resolution)
	{
		ComboBox_Resolution->OnSelectionChanged.AddDynamic(this, &UGraphicSetting::ResolutionBoxOnChagned);
	}
	if (ComboBox_Quality)
	{
		ComboBox_Quality->OnSelectionChanged.AddDynamic(this, &UGraphicSetting::ResolutionBoxOnChagned);
	}
	if (ComboBox_ScreenMode)
	{
		ComboBox_ScreenMode->OnSelectionChanged.AddDynamic(this, &UGraphicSetting::ResolutionBoxOnChagned);
	}

	SetResolutionList();
}

void UGraphicSetting::SetResolutionList()
{
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	for (FIntPoint Resolution : Resolutions)
	{
		FString ResolutionString;

		ResolutionString.Append(FString::FromInt(Resolution.X));
		ResolutionString.Append(" x ");
		ResolutionString.Append(FString::FromInt(Resolution.Y));

		ComboBox_Resolution->AddOption(ResolutionString);
	}
}

void UGraphicSetting::ResolutionBoxOnChagned(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 SelectedIndex = ComboBox_Resolution->GetSelectedIndex();

	if (SelectedIndex >= 0)
	{
		UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
		Setting->SetScreenResolution(Resolutions[SelectedIndex]);
	}
}

void UGraphicSetting::QualityBoxOnChagned(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 SelectedIndex = ComboBox_Quality->GetSelectedIndex();

	if (SelectedIndex >= 0)
	{
		UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
		Setting->SetOverallScalabilityLevel(SelectedIndex);
	}
}

void UGraphicSetting::ScreenModeBoxOnChagned(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 SelectedIndex = ComboBox_Quality->GetSelectedIndex();
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();

	switch (SelectedIndex)
	{
	case 0:
		Setting->SetFullscreenMode(EWindowMode::Fullscreen);
		break;
	case 1:
		Setting->SetFullscreenMode(EWindowMode::Windowed);
		break;
	case 2:
		Setting->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		break;
	}
}
