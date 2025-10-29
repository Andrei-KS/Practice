// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveActorInteface.h"

// Add default functionality here for any ISaveActorInteface functions that are not pure virtual.

FGuid ISaveActorInteface::GetActorSaveId_Implementation()
{
  FGuid Ret = FGuid();
  Ret.Invalidate();
  return Ret;
}

FSaveActorData ISaveActorInteface::GetSaveData_Implementation()
{
  return FSaveActorData();
}
