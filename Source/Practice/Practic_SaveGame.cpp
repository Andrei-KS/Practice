// Fill out your copyright notice in the Description page of Project Settings.


#include "Practic_SaveGame.h"

void UPractic_SaveGame::SetSaveActorData(TMap<FGuid, FSaveActorData> Data)
{
  SaveableActorData = Data;
}

TMap<FGuid, FSaveActorData> UPractic_SaveGame::GetSaveActorData()
{
  return SaveableActorData;
}

void UPractic_SaveGame::SetCurrentLevel(const FName Level)
{
  CurrentlyLoadedLevel = Level;
}

FName UPractic_SaveGame::GetCurrentLevel()
{
  return CurrentlyLoadedLevel;
}