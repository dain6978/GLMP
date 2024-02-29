#include "QualityDetailWidget.h"

#include "GameFramework/GameUserSettings.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include <Kismet/KismetMathLibrary.h>


void UQualityDetailWidget::NativePreConstruct()
{
	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UQualityDetailWidget::OnClickedExitButton);
	}
	
	CreateQualityButtons();
	SetInitState();
}

// Construct
void UQualityDetailWidget::CreateQualityButtons()
{
	for (EQualityTypeState Type : TEnumRange<EQualityTypeState>())
	{
		if (Type == EQualityTypeState::ResolutionScale)
		{
			continue;
		}
		for (EQualityLevelState Level : TEnumRange<EQualityLevelState>())
		{
			QualityButton = Cast<UQualityButton>(CreateWidget(GetWorld(), QualityButtonClass));
			QualityButton->SetTypeState(Type);
			QualityButton->SetLevelState(Level);

			int32 TypeIndex = static_cast<int32>(Type);
			int32 LevelIndex = static_cast<int32>(Level);
			QualityButtons[TypeIndex][LevelIndex] = QualityButton;

			Cast<UPanelWidget>(Containers->GetChildAt(TypeIndex))->AddChild(QualityButton);
			QualityButton->SetPadding(FMargin(10.f, 0.f, 15.f, 0.f));
		}
	}
}

void UQualityDetailWidget::SetInitState()
{
	// Resolution Scale
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	float Val = Setting->GetResolutionScaleNormalized();
	Slider_ResolutionScale->SetValue(Val);

	FString SliderString = FString::FromInt(UKismetMathLibrary::Round(Val * 100));
	SliderString.Append("%");
	Text_ResolutionScale->SetText(FText::FromString(SliderString));

	// Others

}


// Exit 
void UQualityDetailWidget::OnClickedExitButton()
{
	RemoveFromParent();
}


// Resolution Scale
void UQualityDetailWidget::OnChangedResolutionSlider()
{
	float Val = Slider_ResolutionScale->GetValue();

	FString SliderString = FString::FromInt(UKismetMathLibrary::Round(Val * 100));
	SliderString.Append("%");
	Text_ResolutionScale->SetText(FText::FromString(SliderString));
}

void UQualityDetailWidget::EndCapturedResolutionSlider()
{
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	Setting->SetResolutionScaleNormalized(Slider_ResolutionScale->GetValue());
	Setting->ApplySettings(true);
}
