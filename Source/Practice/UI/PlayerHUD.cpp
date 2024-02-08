// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/TextBlock.h"

void UPlayerHUD::SetAmmo(int CurrentAmmo, int MaxAmmo)
{
  if (IsValid(AmmoCounter))
  {
    AmmoCounter->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"),CurrentAmmo, MaxAmmo)));
  }
}
