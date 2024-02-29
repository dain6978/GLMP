// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QualityStateEnums.h"
#include "QualityButton.generated.h"

/**
 * 
 */
UCLASS()
class GLMP_API UQualityButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetLevelState(EQualityLevelState Level);

	UFUNCTION()
	void SetTypeState(EQualityTypeState Type);

	UFUNCTION()
	EQualityLevelState GetLevelState();

	UFUNCTION()
	EQualityTypeState GetTypeState();

	UFUNCTION()
	void SetButtons(TArray<UQualityButton*> QualityButtons);

	UFUNCTION()
	void UnPressed();

	UFUNCTION()
	void OnPressed();


protected:
	// Variables
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_LevelState;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	TArray<UButton*> Buttons;

	EQualityLevelState QualityLevelState;
	EQualityTypeState QualityTypeState;

	FLinearColor UnPressedColor;
	FLinearColor OnPressedColor;

	// Functions
	virtual void NativePreConstruct() override;

	UFUNCTION()
	void OnClickedButton();
};
