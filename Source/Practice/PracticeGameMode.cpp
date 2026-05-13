// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeGameMode.h"
#include "PracticeCharacter.h"
#include "UObject/ConstructorHelpers.h"

APracticeGameMode::APracticeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void APracticeGameMode::StartPlay()
{
  Super::StartPlay();

#if ENABLE_VISUAL_LOG
  // set this parameter to activate visual logger
  FVisualLogger::Get().SetIsRecording(true);
#endif 
}

void APracticeGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
#if ENABLE_VISUAL_LOG
  // set this parameter to deactivate visual logger
  FVisualLogger::Get().SetIsRecording(false);
#endif

  Super::EndPlay(EndPlayReason);
}


