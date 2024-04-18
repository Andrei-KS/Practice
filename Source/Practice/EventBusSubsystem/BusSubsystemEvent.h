// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BusSubsystemEvent.generated.h"

UENUM(BlueprintType)
enum class EBusSubsystemEventType : uint8
{
  None = 0,
  WeaponUI,
};

class UWeaponUIBusSubsystemEvent;
enum class EWeaponType : uint8;

/**
 * 
 */
UCLASS()
class PRACTICE_API UBusSubsystemEvent : public UObject
{
	GENERATED_BODY()

public:
  template <typename TBusSubsystemEvent>
  static TObjectPtr<TBusSubsystemEvent> Make(TWeakObjectPtr<UObject> sendler)
  {
    static_assert(TIsDerivedFrom<TBusSubsystemEvent, UBusSubsystemEvent>::IsDerived, TEXT("Make<TBusSubsystemEvent>: TBusSubsystemEvent must be a class derived from UBusSubsystemEvent"));
    TObjectPtr<TBusSubsystemEvent> Event = NewObject<TBusSubsystemEvent>();
    TObjectPtr<UBusSubsystemEvent> BusSubsystemEvent = static_cast<TObjectPtr<UBusSubsystemEvent>>(Event);
    BusSubsystemEvent.Get()->Type = BusSubsystemEvent.Get()->GetCurrentClassEventType();
    BusSubsystemEvent.Get()->Sendler = sendler;
    return Event;
  }

  void Send();
  const TWeakObjectPtr<UObject> GetSendler() { return Sendler; }
  virtual EBusSubsystemEventType GetCurrentClassEventType() { return EBusSubsystemEventType::None; }

  EBusSubsystemEventType GetEventType() { return Type; }
  
  virtual ~UBusSubsystemEvent();

protected:
  UBusSubsystemEvent();


private:
  EBusSubsystemEventType Type;
  TWeakObjectPtr<UObject> Sendler;
};


/**
 *
 */
UCLASS()
class PRACTICE_API UWeaponUIBusSubsystemEvent : public UBusSubsystemEvent
{
  GENERATED_BODY()
public:
  virtual ~UWeaponUIBusSubsystemEvent();
  virtual EBusSubsystemEventType GetCurrentClassEventType() override { return EBusSubsystemEventType::WeaponUI; }

  EWeaponType WeaponType;
  int AmmoAmount;
  int MaxAmmoAmount;

protected:

  UWeaponUIBusSubsystemEvent();
};