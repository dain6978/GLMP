#include "QualityButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include <VisualLogger/VisualLoggerTypes.h>

void UQualityButton::NativePreConstruct()
{
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UQualityButton::OnClickedButton);
	}
	UnPressedColor = FLinearColor(1.0f, 1.0f, 1.0f);
	OnPressedColor = FLinearColor(0.1f, 0.1f, 0.1f);
}

void UQualityButton::SetLevelState(EQualityLevelState Level)
{
	QualityLevelState = Level;
	FString LevelString = EnumToString("EQualityLevelState", QualityLevelState);
	Text_LevelState->SetText(FText::FromString(LevelString));
}

void UQualityButton::SetTypeState(EQualityTypeState Type)
{
	QualityTypeState = Type;
}

EQualityLevelState UQualityButton::GetLevelState()
{
	return QualityLevelState;
}

EQualityTypeState UQualityButton::GetTypeState()
{
	return QualityTypeState;
}


void UQualityButton::SetButtons(TArray<UQualityButton*> QualityButtons)
{
	for (int32 i = 0; i < QualityButtons.Num(); i++)
	{
		Buttons.Add(QualityButtons[i]->Button);
	}
}

void UQualityButton::UnPressed()
{	
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		Buttons[i]->SetBackgroundColor(UnPressedColor);
	}
}

void UQualityButton::OnPressed()
{
	Button->SetBackgroundColor(OnPressedColor);

	int32 QualityLevelIndex = static_cast<int32>(QualityLevelState);
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();

	switch (QualityTypeState)
	{
	case EQualityTypeState::ViewDistance:
		Setting->SetViewDistanceQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::AntiAliasing:
		Setting->SetAntiAliasingQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::PostProcessing:
		Setting->SetPostProcessingQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::Shadows:
		Setting->SetShadowQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::GlobalIllumination:
		Setting->SetGlobalIlluminationQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::Reflection:
		Setting->SetReflectionQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::Textures:
		Setting->SetTextureQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::Effects:
		Setting->SetVisualEffectQuality(QualityLevelIndex);
		break;
	case EQualityTypeState::Foliage:
		Setting->SetFoliageQuality(QualityLevelIndex);
		break;
	}
}

void UQualityButton::OnClickedButton()
{
	UnPressed();
	OnPressed();
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	Setting->ApplySettings(true);
}
