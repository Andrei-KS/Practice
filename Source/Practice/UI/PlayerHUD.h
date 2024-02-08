// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PRACTICE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
  /** Update HUD with current ammo. */
  void SetAmmo(int CurrentAmmo, int MaxAmmo);

  /** Widgit to use to display current ammo. */
  UPROPERTY(EditAnywhere, meta = (BindWidget))
  class UTextBlock* AmmoCounter;
};
