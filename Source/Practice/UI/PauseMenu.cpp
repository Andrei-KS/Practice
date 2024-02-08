// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenu::NativeConstruct()
{
  if (IsValid(ContinueBtn))
  {
    ContinueBtn->OnClicked.AddDynamic(this,&UPauseMenu::ContinueBtnClicked);
  }

  if (IsValid(QuitBtn))
  {
    QuitBtn->OnClicked.AddDynamic(this, &UPauseMenu::QuitBtnBtnClicked);
  }
}

void UPauseMenu::ContinueBtnClicked()
{
  APlayerController* APC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  FInputModeGameOnly InputModeGameOnly;
  APC->SetInputMode(InputModeGameOnly);
  APC->SetShowMouseCursor(false);
  RemoveFromParent();
  UGameplayStatics::SetGamePaused(GetWorld(),false);
}

void UPauseMenu::QuitBtnBtnClicked()
{
  TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
  UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitPreference, true);
}
