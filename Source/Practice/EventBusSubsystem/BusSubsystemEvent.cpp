// Fill out your copyright notice in the Description page of Project Settings.

#include "BusSubsystemEvent.h"
#include "Engine/GameInstance.h"
#include "EventBusSubsystem.h"
#include "../TP_WeaponComponent.h"

void UBusSubsystemEvent::Send()
{

  UWorld* World = GetSendler()->GetWorld();
  if (World == nullptr)
  {
    return;
  }

  UGameInstance* GameInstance = World->GetGameInstance();
  if (GameInstance == nullptr)
  {
    return;
  }

  UEventBusSubsystem* EventBusSubsystem = GameInstance->GetSubsystem<UEventBusSubsystem>();
  if (EventBusSubsystem == nullptr)
  {
    return;
  }
  EventBusSubsystem->FireEvent(this);
}

UBusSubsystemEvent::~UBusSubsystemEvent()
{
}

UBusSubsystemEvent::UBusSubsystemEvent()
{
}

UWeaponUIBusSubsystemEvent::~UWeaponUIBusSubsystemEvent()
{
}

UWeaponUIBusSubsystemEvent::UWeaponUIBusSubsystemEvent()
{
  WeaponType = EWeaponType::None;
  AmmoAmount = 0;
  MaxAmmoAmount = 0;
}
