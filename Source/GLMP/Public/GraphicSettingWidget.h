#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QualityDetailWidget.h"

#include "GraphicSettingWidget.generated.h"

/**
 *
 */
UCLASS()
class GLMP_API UGraphicSettingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Variables
	TArray<FIntPoint> Resolutions;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* ComboBox_Resolution;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* ComboBox_Quality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* ComboBox_ScreenMode;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Apply;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Cancel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_ChangeSky;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_QualityDetail;


	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> SettingWidgetClass;
	UUserWidget* SettingWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ChangeSkyWidgetClass;
	UUserWidget* ChangeSkyWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> QualityDetailWidgetClass;
	UUserWidget* QualityDetailWidget;


	// Functions
	virtual void NativePreConstruct() override;

	UFUNCTION()
	void SetResolutionList();

	UFUNCTION()
	void OnChangedResolutionBox(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnChangedQualityBox(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnChangedScreenModeBox(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnClickedApplyButton();

	UFUNCTION()
	void OnClickedCancelButton();

	UFUNCTION()
	void OnClickedChangeSkyButton();

	UFUNCTION()
	void OnClickedQualityDetailButton();
};
