// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Practice_GrenadeProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UDamageComponent;

UCLASS()
class PRACTICE_API APractice_GrenadeProjectile : public AActor
{
	GENERATED_BODY()
	
  /** Sphere collision component */
  UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
  USphereComponent* CollisionComp;

  /** Projectile movement component */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
  UProjectileMovementComponent* ProjectileMovement;

  /** Damage component */
  UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
  UDamageComponent* DamageComponent;

public:	
	// Sets default values for this actor's properties
  APractice_GrenadeProjectile();

  /** called when projectile hits something */
  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  /** Returns CollisionComp subobject **/
  USphereComponent* GetCollisionComp() const { return CollisionComp; }

  /** Returns ProjectileMovement subobject **/
  UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

};
