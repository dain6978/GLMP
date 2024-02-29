#include "QualityDetailWidget.h"

#include "GameFramework/GameUserSettings.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include <Kismet/KismetMathLibrary.h>


// Construct
void UQualityDetailWidget::NativePreConstruct()
{
	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UQualityDetailWidget::OnClickedExitButton);
	}
	if (Slider_ResolutionScale)
	{
		Slider_ResolutionScale->OnValueChanged.AddDynamic(this, &UQualityDetailWidget::OnChangedResolutionSlider);
		Slider_ResolutionScale->OnMouseCaptureEnd.AddDynamic(this, &UQualityDetailWidget::EndCapturedResolutionSlider);
	}

	CreateQualityButtons();
	SetInitState();
}

void UQualityDetailWidget::CreateQualityButtons()
{
	for (EQualityTypeState Type : TEnumRange<EQualityTypeState>())
	{
		if (Type == EQualityTypeState::ResolutionScale)
			continue;

		int32 TypeIndex = static_cast<int32>(Type) - 1; // Resolution Scale 제외
		QualityButtons.Add(TArray<UQualityButton*>());

		for (EQualityLevelState Level : TEnumRange<EQualityLevelState>())
		{
			QualityButton = Cast<UQualityButton>(CreateWidget(GetWorld(), QualityButtonClass));
			QualityButton->SetTypeState(Type);
			QualityButton->SetLevelState(Level);

			QualityButtons[TypeIndex].Add(QualityButton); 

			Cast<UPanelWidget>(Containers->GetChildAt(TypeIndex + 1))->AddChild(QualityButton); // Containers의 자식에 Resolution Scale Slider 포함 -> + 1
			QualityButton->SetPadding(FMargin(10.f, 0.f, 15.f, 0.f));
		}
		for (UQualityButton* QualityLevelButton : QualityButtons[TypeIndex]) // 같은 Type, 다른 Level의 버튼들
		{
			QualityLevelButton->SetButtons(QualityButtons[TypeIndex]);
		}
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
		if (Type == EQualityTypeState::ResolutionScale)
			continue;

		int32 TypeIndex = static_cast<int32>(Type) - 1; // Resolution Scale 제외
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
		case EQualityTypeState::Shading:
			LevelIndex = Setting->GetShadingQuality();
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
void UQualityDetailWidget::OnChangedResolutionSlider(float Val)
{
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
