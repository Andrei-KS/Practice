// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveActorInteface.generated.h"

USTRUCT(BlueprintType)
struct FSaveActorData
{
  GENERATED_USTRUCT_BODY()

public:
  UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
  FTransform ActorTransform;

  UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
  TArray<uint8> ByteData;

  UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
  bool WasSpawned = false;

  UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
  UClass* ActorClass;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveActorInteface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRACTICE_API ISaveActorInteface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

  UFUNCTION(BlueprintNativeEvent)
  FGuid GetActorSaveId();
  virtual FGuid GetActorSaveId_Implementation();

  UFUNCTION(BlueprintNativeEvent)
  FSaveActorData GetSaveData();
  virtual FSaveActorData GetSaveData_Implementation();
};
