// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicSetting.h"

#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"


void UGraphicSetting::NativePreConstruct()
{
	SetResolutionList();
}

void UGraphicSetting::SetResolutionList()
{
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	UGameUserSettings* setting = UGameUserSettings::GetGameUserSettings();

	for (FIntPoint Resolution : Resolutions) 
	{
		FString ResolutionString;

		ResolutionString.Append(FString::FromInt(Resolution.X));
		ResolutionString.Append(FString::FromInt(" x "));
		ResolutionString.Append(FString::FromInt(Resolution.Y));

		/*ComboBox_Resolution->AddOption(TEXT(ResolutionString));*/
	}
}