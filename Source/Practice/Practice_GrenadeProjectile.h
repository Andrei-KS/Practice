// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PracticeProjectile.h"
#include "Practice_GrenadeProjectile.generated.h"

// Forward declare this class, so the header file knows it is valid
class UNiagaraSystem;
class UNiagaraComponent;
class UDamageComponent;
class USplineComponent;

UCLASS()
class PRACTICE_API APractice_GrenadeProjectile : public APracticeProjectile
{
	GENERATED_BODY()

  /** Damage component */
  UPROPERTY(VisibleDefaultsOnly, Category = "Grenade")
  UDamageComponent* ExplodionDamageComponent;

public:
  APractice_GrenadeProjectile();

  virtual void Tick(float DeltaSeconds) override;

protected:
  /** Setup character when game starts. */
  virtual void BeginPlay();

  // This enables the user to pick any Niagara System in the component's Blueprint Details panel in the editor
  /** Muzzle flash effect, leave empty if none is desired */
  UPROPERTY(EditDefaultsOnly, Category = "Grenade")
  UNiagaraSystem* FireEffectMuzzle;
  
  UPROPERTY(EditDefaultsOnly, Category = "Grenade")
  float FuseLenght;

  UPROPERTY(EditDefaultsOnly, Category = "Grenade")
  float ExplotionRadius;

  virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

  void Explode();

  UPROPERTY(VisibleAnywhere, Category = "TraveledPath")
  USplineComponent* TraveledPathSplineComponent;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraveledPath")
  UNiagaraComponent* TraveledPathVisualEffect;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraveledPath")
  UStaticMesh* SplaneMesh;

private:
  TArray<FVector> TraveledPath;
};
