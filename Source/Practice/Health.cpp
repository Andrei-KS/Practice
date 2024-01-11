// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();
}

void UHealth::ReduceHealthBy(int DamageValue)
{
  
  if (bIsImmortal)
  {
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Object get hit, but this object is immortal")));
    return;
  }

  Health -= DamageValue;
  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Object get hit, DamageValue %d, remaing %d health"), DamageValue, Health));

  if (Health <= 0)
  {
    GetOwner()->Destroy();
  }
}


