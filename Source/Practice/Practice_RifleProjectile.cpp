// Fill out your copyright notice in the Description page of Project Settings.


#include "Practice_RifleProjectile.h"

void APractice_RifleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

  if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
  {
    Destroy();
  }
}
