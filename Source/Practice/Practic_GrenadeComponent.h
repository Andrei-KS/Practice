// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "Practic_GrenadeComponent.generated.h"

class APracticeCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PRACTICE_API UPractic_GrenadeComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPractic_GrenadeComponent();

  /** Make the weapon Use a Projectile */
  virtual void Use() override;

};
