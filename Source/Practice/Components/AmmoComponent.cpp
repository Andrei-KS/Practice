// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"
#include "../PracticeCharacter.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAmmoComponent::PickedUpBy(APracticeCharacter* TargetCharacter)
{
  // Check that the character is valid, and has no rifle yet
  if (TargetCharacter == nullptr)
  {
    return;
  }

  TargetCharacter->AddAmmo(AmmoAmount);
  GetOwner()->Destroy();
}

