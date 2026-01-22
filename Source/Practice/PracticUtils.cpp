// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticUtils.h"


// Val1|Val2|Val3 -> {Val1, Val2, Val3}
TArray<FString> ChopString(FString Source, char split)
{
  TArray<FString> Ret;
  FString Push;
  for (int it = 0; it < static_cast<int>(Source.Len()); ++it)
  {
    if (Source[it] == split)
    {
      Ret.Add(Push);
      Push.Empty();
    }
    else
    {
      Push += Source[it];
    }
  }

  if (!Push.IsEmpty())
  {
    Ret.Add(Push);
  }

  return Ret;
}
