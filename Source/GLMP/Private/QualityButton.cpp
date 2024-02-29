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

void UQualityButton::UnPressed()
{	

}

void UQualityButton::OnPressed()
{
}

void UQualityButton::OnClickedButton()
{
	UnPressed();
	OnPressed();
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	Setting->ApplySettings(true);
}
