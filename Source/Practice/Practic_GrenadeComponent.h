// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Practic_GrenadeComponent.generated.h"

class APracticeCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PRACTICE_API UPractic_GrenadeComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
  /** Projectile class to spawn */
  UPROPERTY(EditDefaultsOnly, Category = Projectile)
  TSubclassOf<class APractice_GrenadeProjectile> GrenadeProjectileClass;

  /** Gun muzzle's offset from the characters location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
  FVector MuzzleOffset;

  /** MappingContext */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputMappingContext* ThrowMappingContext;

  /** Throw Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* ThrowAction;

	// Sets default values for this component's properties
	UPractic_GrenadeComponent();

  /** Attaches the actor to a FirstPersonCharacter */
  UFUNCTION(BlueprintCallable, Category = "Weapon")

  void AttachWeapon(APracticeCharacter* TargetCharacter);
  /** Attaches the actor to a FirstPersonCharacter hand */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  void AttachWeaponToHand();

  /** Attaches the actor to a FirstPersonCharacter hand */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  void AttachWeaponToInventory();

  /** Enabale weapon */
  void EnableWeapon();

  /** Disenabale weapon */
  void DisabaleWeapon();

  /** Make the weapon Fire a Projectile */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  void Throw();

protected:
  /** Ends gameplay for this component. */
  UFUNCTION()
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
  /** The Character holding this weapon*/
  APracticeCharacter* Character;
};
