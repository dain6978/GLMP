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
		QualityButton->SetButtons(QualityButtons[static_cast<int32>(Type)]);
	}
}

void UQualityDetailWidget::SetInitState()
{
	UGameUserSettings* Setting = UGameUserSettings::GetGameUserSettings();
	// Resolution Scale

	float Val = Setting->GetResolutionScaleNormalized();
	Slider_ResolutionScale->SetValue(Val);

	FString SliderString = FString::FromInt(UKismetMathLibrary::Round(Val * 100));
	SliderString.Append("%");
	Text_ResolutionScale->SetText(FText::FromString(SliderString));

	// Others
	for (EQualityTypeState Type : TEnumRange<EQualityTypeState>())
	{
		int32 TypeIndex = static_cast<int32>(Type);
		int32 LevelIndex;

		switch (Type)
		{
		case EQualityTypeState::ViewDistance:
			LevelIndex = Setting->GetViewDistanceQuality();
			break;
		case EQualityTypeState::AntiAliasing:
			LevelIndex = Setting->GetAntiAliasingQuality();
			break;
		case EQualityTypeState::PostProcessing:
			LevelIndex = Setting->GetPostProcessingQuality();
			break;
		case EQualityTypeState::Shadows:
			LevelIndex = Setting->GetShadowQuality();
			break;
		case EQualityTypeState::GlobalIllumination:
			LevelIndex = Setting->GetGlobalIlluminationQuality();
			break;
		case EQualityTypeState::Reflection:
			LevelIndex = Setting->GetReflectionQuality();
			break;
		case EQualityTypeState::Textures:
			LevelIndex = Setting->GetTextureQuality();
			break;
		case EQualityTypeState::Effects:
			LevelIndex = Setting->GetVisualEffectQuality();
			break;
		case EQualityTypeState::Foliage:
			LevelIndex = Setting->GetFoliageQuality();
			break;
		}
		
		QualityButtons[TypeIndex][LevelIndex]->OnPressed();
	}
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
