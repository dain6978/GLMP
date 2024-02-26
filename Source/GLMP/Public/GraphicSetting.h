// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "GraphicSetting.generated.h"

/**
 * 
 */
UCLASS()
class GLMP_API UGraphicSetting : public UUserWidget
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


	// Functions
	virtual void NativePreConstruct() override;

	UFUNCTION()
	void SetResolutionList();

	UFUNCTION()
	void ResolutionBoxOnChagned(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void QualityBoxOnChagned(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void ScreenModeBoxOnChagned(FString SelectedItem, ESelectInfo::Type SelectionType);
};
