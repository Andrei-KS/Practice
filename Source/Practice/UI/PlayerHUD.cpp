// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/TextBlock.h"
#include "../PracticeCharacter.h"

void UPlayerHUD::SetAmmo(EWeaponType Type, int CurrentAmmoValue, int MaxAmmoValue)
{
  if (IsValid(AmmoCounter) && IsValid(WeaponType))
  {
    switch (Type)
    {
    case EWeaponType::None:
      WeaponType->SetText(FText::FromString(FString::Printf(TEXT("None"))));
      AmmoCounter->SetText(FText::FromString(FString::Printf(TEXT(""))));
      break;
    case EWeaponType::Rifle:
      WeaponType->SetText(FText::FromString(FString::Printf(TEXT("Rifle"))));
      CurrentAmmo = CurrentAmmoValue;
      MaxAmmo = MaxAmmoValue;
      PlayAnimation(Increase, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
      break;
    case EWeaponType::Grenade:
      WeaponType->SetText(FText::FromString(FString::Printf(TEXT("Grenade"))));
      AmmoCounter->SetText(FText::FromString(FString::Printf(TEXT("inf"))));
      break;
    default:
      break;
    }
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
