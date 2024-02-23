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
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget));
	//class UButton* Button_Apply;
	//
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget));
	//class UButton* Button_Cancel;

	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget));
	//class UButton* Button_QuailtyDetail;

	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget));
	//class UComboBox* ComboBox_Quality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget));
	class UComboBox* ComboBox_Resolution;

	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget));
	//class UComboBox* ComboBox_ScreenMode;
	
	UPROPERTY(BlueprintReadOnly, Category = "Graphic Setting");
	TArray<FIntPoint> Resolutions;

	
	// Functions
	virtual void NativePreConstruct() override;


	void SetResolutionList();
};
