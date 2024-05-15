// Fill out your copyright notice in the Description page of Project Settings.

#include "BusSubsystemEventHandler.h"
#include "BusSubsystemEvent.h"
#include "Engine/GameInstance.h"
#include "EventBusSubsystem.h"

UBusSubsystemEventHandler::~UBusSubsystemEventHandler()
{
  UnRegistrateInSubsystem();
}

void UBusSubsystemEventHandler::HandleEvent(TObjectPtr<UBusSubsystemEvent> Event)
{
  if (OnHandledEvent.IsBound())
  {
    OnHandledEvent.Broadcast(Event);
  }
}

void UBusSubsystemEventHandler::RegistrateInSubsystem(EBusSubsystemEventType Type)
{
  SetEventBusSubsystem();
  EventBusSubsystem->RegistrateHandler(this, Type);
}

void UBusSubsystemEventHandler::UnRegistrateInSubsystem()
{
  if (EventBusSubsystem.IsValid())
  {
    EventBusSubsystem->UnregistrateHandler(this);
  }
}

void UBusSubsystemEventHandler::SetEventBusSubsystem()
{
  UWorld* World = Owner->GetWorld();
  if (World == nullptr)
  {
    return;
  }

  UGameInstance* GameInstance = World->GetGameInstance();
  if (GameInstance == nullptr)
  {
    return;
  }

  EventBusSubsystem = GameInstance->GetSubsystem<UEventBusSubsystem>();
}
