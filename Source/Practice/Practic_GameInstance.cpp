// Fill out your copyright notice in the Description page of Project Settings.


#include "Practic_GameInstance.h"
#include "Practic_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

/*
  location
  rotation
  scale

  tranform

  health

  inventory
  ammo

  was harvested:
  number off hits
*/
UPractic_GameInstance::UPractic_GameInstance()
{
}


void UPractic_GameInstance::CreateSaveSlot()
{
  SaveGameObject = Cast<UPractic_SaveGame>(UGameplayStatics::CreateSaveGameObject(UPractic_SaveGame::StaticClass()));
}

void UPractic_GameInstance::GatherActorData()
{
  for (FActorIterator It(GetWorld()); It; ++It)
  {
    AActor* Actor = *It;
    if (!IsValid(Actor) || !Actor->Implements<USaveActorInteface>())
    {
      continue;
    }

    ISaveActorInteface* SAInterface = Cast<ISaveActorInteface>(Actor);
    if (SAInterface == nullptr)
    {
      continue;
    }

    FGuid SaveActorId = SAInterface->GetActorSaveId_Implementation();
    if (!SaveActorId.IsValid())
    {
      continue;
    }

    FSaveActorData SaveActorData = SAInterface->GetSaveData_Implementation();
    FMemoryWriter MemoryWriter(SaveActorData.ByteData);
    FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
    Archive.ArIsSaveGame = true;
    Actor->Serialize(Archive);

    SaveableActorData.Add(SaveActorId, SaveActorData);
  }
}

void UPractic_GameInstance::AddActorData(const FGuid& ActorId, FSaveActorData ActorData)
{
  SaveableActorData.Add(ActorId, ActorData);
}

FSaveActorData UPractic_GameInstance::GetActorData(const FGuid& ActorId)
{
  return SaveableActorData[ActorId];
}

void UPractic_GameInstance::DEV_SaveGame()
{
  if (SaveGameObject == nullptr)
  {
    CreateSaveSlot();
  }
  GatherActorData();
  SaveGameObject->SetSaveActorData(SaveableActorData);
  UGameplayStatics::SaveGameToSlot(SaveGameObject,SaveGameName, 0);
}
