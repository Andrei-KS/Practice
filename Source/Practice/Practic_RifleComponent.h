// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "Practic_RifleComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PRACTICE_API UPractic_RifleComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()
	
public:
  /** Sets default values for this component's properties */
  UPractic_RifleComponent();

  /** Make the weapon Use a Projectile */
  virtual void Use() override;

};
