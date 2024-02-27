#include "QualityDetailWidget.h"

#include "GameFramework/GameUserSettings.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include <Kismet/KismetMathLibrary.h>


void UQualityDetailWidget::NativePreConstruct()
{
}

void UQualityDetailWidget::CreateQualityButtons()
{
}

void UQualityDetailWidget::SetInitState()
{
	// Resolution Scale
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	float SliderVal = Setting->GetResolutionScaleNormalized();
	Slider_ResolutionScale->SetValue(SliderVal);

	FString SliderString = FString::FromInt(UKismetMathLibrary::Round(SliderVal * 100));
	SliderString.Append("%");
	Text_ResolutionScale->SetText(FText::FromString(SliderString));

	// Others

}

void UQualityDetailWidget::OnClickedExitButton()
{
	RemoveFromParent();
}
