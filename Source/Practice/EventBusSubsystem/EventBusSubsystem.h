// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EventBusSubsystem.generated.h"

//UEventBusSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UEventBusSubsystem>();

class UBusSubsystemEvent;
class UBusSubsystemEventHandler;
enum class EBusSubsystemEventType : uint8;

/**
 * 
 */
UCLASS()
class PRACTICE_API UEventBusSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
  // Begin USubsystem
  virtual void Initialize(FSubsystemCollectionBase& Collection) override;
  virtual void Deinitialize() override;
  // End USubsystem

  void FireEvent(TObjectPtr<UBusSubsystemEvent> BusSubsystemEvent);
  void RegistrateHandler(TObjectPtr<UBusSubsystemEventHandler> Handler, EBusSubsystemEventType Type);
  void UnregistrateHandler(TObjectPtr<UBusSubsystemEventHandler> Handler);

private:
  TMap<EBusSubsystemEventType, TSet<TObjectPtr<UBusSubsystemEventHandler>>> Handlers;
};
