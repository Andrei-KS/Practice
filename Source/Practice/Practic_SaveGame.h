// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Interface/SaveActorInteface.h"
#include "Practic_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UPractic_SaveGame : public USaveGame
{
	GENERATED_BODY()
  
private:
  UPROPERTY()
  TMap<FGuid, FSaveActorData> SaveableActorData;
  
  UPROPERTY()
  FName CurrentlyLoadedLevel = "NONE";

public:
  void SetSaveActorData(TMap<FGuid, FSaveActorData> Data);
  TMap<FGuid, FSaveActorData> GetSaveActorData();
  void SetCurrentLevel(const FName Level);
  FName GetCurrentLevel();
	
};
