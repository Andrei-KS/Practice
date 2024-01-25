// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
  Super::BeginPlay();
}

void UHealthComponent::ApplyDamage(int DamageValue)
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


