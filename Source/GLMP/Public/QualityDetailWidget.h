// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QualityDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class GLMP_API UQualityDetailWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> QualityButtonClass;
	UUserWidget* QualityButton;

	// TArray<TArray<QualityButton>> QualityButtons;

	// Variables
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Exit;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* Slider_ResolutionScale;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_ResolutionScale;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* Containers;


	// Functions
	virtual void NativePreConstruct() override;

	UFUNCTION()
	void CreateQualityButtons();

	UFUNCTION()
	void SetInitState();


	UFUNCTION()
	void OnClickedExitButton();
};
