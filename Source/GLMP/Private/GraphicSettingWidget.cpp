#include "GraphicSettingWidget.h"

#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"


void UGraphicSettingWidget::NativePreConstruct()
{
	if (ComboBox_Resolution)
	{
		ComboBox_Resolution->OnSelectionChanged.AddDynamic(this, &UGraphicSettingWidget::OnChangedResolutionBox);
	}
	if (ComboBox_Quality)
	{
		ComboBox_Quality->OnSelectionChanged.AddDynamic(this, &UGraphicSettingWidget::OnChangedQualityBox);
	}
	if (ComboBox_ScreenMode)
	{
		ComboBox_ScreenMode->OnSelectionChanged.AddDynamic(this, &UGraphicSettingWidget::OnChangedScreenModeBox);
	}
	if (Button_Apply)
	{
		Button_Apply->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnClickedApplyButton);
	}
	if (Button_Cancel)
	{
		Button_Cancel->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnClickedCancelButton);
	}
	if (Button_ChangeSky)
	{
		Button_ChangeSky->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnClickedChangeSkyButton);
	}
	if (Button_QualityDetail)
	{
		Button_QualityDetail->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnClickedQualityDetailButton);
	}

	SetResolutionList();
}

void UGraphicSettingWidget::SetResolutionList()
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

void UGraphicSettingWidget::OnChangedResolutionBox(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 SelectedIndex = ComboBox_Resolution->GetSelectedIndex();

	if (SelectedIndex >= 0)
	{
		UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
		Setting->SetScreenResolution(Resolutions[SelectedIndex]);
	}
}

void UGraphicSettingWidget::OnChangedQualityBox(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 SelectedIndex = ComboBox_Quality->GetSelectedIndex();

	if (SelectedIndex >= 0)
	{
		UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
		Setting->SetOverallScalabilityLevel(SelectedIndex);
	}
}

void UGraphicSettingWidget::OnChangedScreenModeBox(FString SelectedItem, ESelectInfo::Type SelectionType)
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

void UGraphicSettingWidget::OnClickedApplyButton()
{
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	Setting->ApplySettings(true);
}

void UGraphicSettingWidget::OnClickedCancelButton()
{
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	Setting->ResetToCurrentSettings();

	RemoveFromParent();
	
	SettingWidget = CreateWidget(GetWorld(), SettingWidgetClass);
	if (SettingWidget != nullptr)
	{
		SettingWidget->AddToViewport();
	}
}

void UGraphicSettingWidget::OnClickedChangeSkyButton()
{
	ChangeSkyWidget = CreateWidget(GetWorld(), ChangeSkyWidgetClass);
	if (ChangeSkyWidget != nullptr)
	{
		ChangeSkyWidget->AddToViewport();
	}

	RemoveFromParent();
}

void UGraphicSettingWidget::OnClickedQualityDetailButton()
{
	QualityDetailWidget = CreateWidget(GetWorld(), QualityDetailWidgetClass);
	if (QualityDetailWidget != nullptr)
	{
		QualityDetailWidget->AddToViewport();
	}
}
