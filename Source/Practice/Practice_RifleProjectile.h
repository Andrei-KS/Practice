// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PracticeProjectile.h"
#include "Practice_RifleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API APractice_RifleProjectile : public APracticeProjectile
{
	GENERATED_BODY()
	
public:
  virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
