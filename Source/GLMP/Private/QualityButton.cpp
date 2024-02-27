#include "QualityButton.h"

#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

void UQualityButton::NativePreConstruct()
{
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UQualityButton::OnClickedButton);
	}
}

void UQualityButton::OnClickedButton()
{
	OnPressed();
	UnPressed();
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	Setting->ApplySettings(true);
}

void UQualityButton::OnPressed()
{
}

void UQualityButton::UnPressed()
{
}
