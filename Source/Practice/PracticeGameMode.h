// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PracticeGameMode.generated.h"

UCLASS(minimalapi)
class APracticeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APracticeGameMode();

protected:
  virtual void StartPlay() override;
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};



