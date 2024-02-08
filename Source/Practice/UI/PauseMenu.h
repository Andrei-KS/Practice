// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PRACTICE_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, meta = (BindWidget))
  class UTextBlock* TitleText;

  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  class UButton* ContinueBtn;

  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  class UButton* QuitBtn;

  virtual void NativeConstruct() override;

  UFUNCTION()
  void ContinueBtnClicked();

  UFUNCTION()
  void QuitBtnBtnClicked();
};
