// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class APracticeCharacter;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
  None = 0,
  Rifle,
  Grenade,
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class APracticeProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* UseSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* UseAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* UseMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* UseAction;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
  virtual void AttachWeapon(APracticeCharacter* TargetCharacter);

  /** Attaches the actor to a FirstPersonCharacter hand */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  virtual void AttachWeaponToHand();

  /** Attaches the actor to a FirstPersonCharacter hand */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  virtual void AttachWeaponToInventory();

  UFUNCTION(BlueprintCallable, Category = "Weapon")
  EWeaponType GetWeaponType() const { return WeaponType; };

  /** Enabale weapon */
  virtual void EnableWeapon();

  /** Disenabale weapon */
  virtual void DisabaleWeapon();

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void Use();

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** The Character holding this weapon*/
	APracticeCharacter* Character;

  /** The Weapon Type is this weapon*/
  EWeaponType WeaponType;
};
