// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDamageComponent::ApplyDamageTo(AActor* target)
{
  UHealthComponent* otherActorHealth = target->FindComponentByClass<UHealthComponent>();
  if (IsValid(otherActorHealth))
  {
    otherActorHealth->ApplyDamage(DamageValue);
  }
}
