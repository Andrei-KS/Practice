// Fill out your copyright notice in the Description page of Project Settings.


#include "EventBusSubsystem.h"
#include "BusSubsystemEvent.h"
#include "BusSubsystemEventHandler.h"

void UEventBusSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
  Super::Initialize(Collection);
  UE_LOG(LogTemp, Warning, TEXT("UEventBusSubsystem started"));
}

void UEventBusSubsystem::Deinitialize()
{
  Super::Deinitialize();
}

void UEventBusSubsystem::FireEvent(TObjectPtr<UBusSubsystemEvent> BusSubsystemEvent)
{
  UE_LOG(LogTemp, Warning, TEXT("UEventBusSubsystem::FireEvent executed successfully, event type %d"), BusSubsystemEvent.Get()->GetEventType());
  TSet<TObjectPtr<UBusSubsystemEventHandler>>* Category = Handlers.Find(BusSubsystemEvent->GetEventType());
  if (Category != nullptr)
  {
    for (auto& Handler : *Category)
    {
      Handler->HandleEvent(BusSubsystemEvent);
    }
  }
}

void UEventBusSubsystem::RegistrateHandler(TObjectPtr<UBusSubsystemEventHandler> Handler, EBusSubsystemEventType Type)
{
  TSet<TObjectPtr<UBusSubsystemEventHandler>>* Category = Handlers.Find(Type);
  if (Category == nullptr)
  {
    Handlers.Add(Type, TSet<TObjectPtr<UBusSubsystemEventHandler>>{ Handler });
  }
  else
  {
    Category->Add(Handler);
  }
}

void UEventBusSubsystem::UnregistrateHandler(TObjectPtr<UBusSubsystemEventHandler> Handler)
{
  for (auto& CategoryHandlers : Handlers)
  {
    CategoryHandlers.Value.Remove(Handler);
  }
}
