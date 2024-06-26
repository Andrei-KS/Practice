// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

enum class EWeaponType : uint8;
class UBusSubsystemEventHandler;
class UBusSubsystemEvent;

/**
 * 
 */
UCLASS(Abstract)
class PRACTICE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
  /** Update HUD with current ammo. */
  UFUNCTION()
  void UpdateWeaponUI(UBusSubsystemEvent* Event);

  /** Widgit to use to display current ammo. */
  UPROPERTY(EditAnywhere, meta = (BindWidget))
  class UTextBlock* WeaponType;

  /** Widgit to use to display current ammo. */
  UPROPERTY(EditAnywhere, meta = (BindWidget))
  class UTextBlock* AmmoCounter;

protected:

  virtual void NativeConstruct() override;

  UPROPERTY(EditAnywhere, Transient, meta=(BindWidgetAnim))
  class UWidgetAnimation* Increase;

  UPROPERTY(EditAnywhere, Transient, meta=(BindWidgetAnim))
  class UWidgetAnimation* Decrease;

  FWidgetAnimationDynamicEvent StartDelegate;
  FWidgetAnimationDynamicEvent EndDelegate;

private:
  UPROPERTY(EditAnywhere)
  TObjectPtr<UBusSubsystemEventHandler> WeaponUIHadler;

  UFUNCTION()
  void AnimationStarted();

  UFUNCTION()
  void AnimationFinished();

  int CurrentAmmo;
  int MaxAmmo;
};
