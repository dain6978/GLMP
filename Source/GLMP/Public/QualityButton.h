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


protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_LevelState;

	EQualityLevelState QualityLevelState;
	EQualityTypeState QualityTypeState;

	TArray<UButton*> Buttons;


	virtual void NativePreConstruct() override;

	UFUNCTION()
	void UnPressed();

	UFUNCTION()
	void OnPressed();

	UFUNCTION()
	void OnClickedButton();
};
