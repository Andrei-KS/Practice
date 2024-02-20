// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/TextBlock.h"

void UPlayerHUD::SetAmmo(int CurrentAmmoValue, int MaxAmmoValue)
{
  if (IsValid(AmmoCounter))
  {
    CurrentAmmo = CurrentAmmoValue;
    MaxAmmo = MaxAmmoValue;
    PlayAnimation(Increase, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
  }
}

void UPlayerHUD::NativeConstruct()
{
  Super::NativeConstruct();

  StartDelegate.BindDynamic(this, &UPlayerHUD::AnimationStarted);
  EndDelegate.BindDynamic(this, &UPlayerHUD::AnimationFinished);

  BindToAnimationStarted(Decrease, StartDelegate);
  BindToAnimationFinished(Increase, EndDelegate);

  CurrentAmmo = 0;
  MaxAmmo = 0;
}

void UPlayerHUD::AnimationStarted()
{
}

void UPlayerHUD::AnimationFinished()
{
  AmmoCounter->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentAmmo, MaxAmmo)));
  CurrentAmmo = 0;
  MaxAmmo = 0;
  PlayAnimation(Decrease, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}
