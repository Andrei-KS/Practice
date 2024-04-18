// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BusSubsystemEvent.h"
#include "BusSubsystemEventHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHandledEvent, UBusSubsystemEvent*, Event);

/**
 * 
 */
UCLASS(BlueprintType)
class PRACTICE_API UBusSubsystemEventHandler : public UObject
{
	GENERATED_BODY()

public:
  template <typename TBusSubsystemEvent>
  static TObjectPtr<UBusSubsystemEventHandler> Make(TWeakObjectPtr<UObject> Owner)
  {
    static_assert(TIsDerivedFrom<TBusSubsystemEvent, UBusSubsystemEvent>::IsDerived, TEXT("Make<TBusSubsystemEvent>: TBusSubsystemEvent must be a class derived from UBusSubsystemEvent"));
    TObjectPtr<UBusSubsystemEventHandler> EventHandler = NewObject<UBusSubsystemEventHandler>();
    EventHandler.Get()->Owner = Owner;
    TObjectPtr<UBusSubsystemEvent> BusSubsystemEvent = static_cast<TObjectPtr<UBusSubsystemEvent>>(NewObject<TBusSubsystemEvent>());
    EventHandler.Get()->RegistrateInSubsystem(BusSubsystemEvent.Get()->GetCurrentClassEventType());
    return EventHandler;
  }
  virtual ~UBusSubsystemEventHandler();
  void HandleEvent(TObjectPtr<UBusSubsystemEvent> Event);

  UPROPERTY(BlueprintAssignable, Category = "BusSubsystemEvent")
  FHandledEvent OnHandledEvent;

private:
  void RegistrateInSubsystem(EBusSubsystemEventType Type);
  void UnRegistrateInSubsystem();
  void SetEventBusSubsystem();
  TWeakObjectPtr<UObject> Owner;
  TWeakObjectPtr<class UEventBusSubsystem> EventBusSubsystem;
};
