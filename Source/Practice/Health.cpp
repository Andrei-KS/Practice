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
  Health -= DamageValue;

  if (Health <= 0)
  {
    GetOwner()->Destroy();
  }
}


