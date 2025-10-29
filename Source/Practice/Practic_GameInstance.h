// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Practice/Interface/SaveActorInteface.h"
#include "Practic_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UPractic_GameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

  // Basic information that need
  TMap<FGuid, FSaveActorData> SaveableActorData;
  UPROPERTY()
  class UPractic_SaveGame* SaveGameObject = nullptr;
  FString SaveGameName = TEXT("DEFAULT");
  FName CurrentlyLoadedLevel = "NONE";
	//

  UPractic_GameInstance();

  void CreateSaveSlot();
  void GatherActorData();

public:
  UFUNCTION(BlueprintCallable)
  void AddActorData(const FGuid& ActorId, FSaveActorData ActorData);

  UFUNCTION(BlueprintCallable)
  FSaveActorData GetActorData(const FGuid& ActorId);

  UFUNCTION(BlueprintCallable)
  void DEV_SaveGame();

};
