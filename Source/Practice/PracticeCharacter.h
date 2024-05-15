// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PracticeCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UTP_WeaponComponent;
enum class EWeaponType : uint8;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APracticeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
  /** Move Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* PauseAction;

  /** TakeRiflInHand Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* TakeRiflInHandAction;

  /** Move Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* TakeGrenadeInHandAction;

public:
	APracticeCharacter();

protected:
  /** Setup character when game starts. */
	virtual void BeginPlay();

  /** Cleanup character when game ends. */
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bIsRifleInHand;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetWeapon(UTP_WeaponComponent* NewWeapon);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
  UTP_WeaponComponent* GetWeapon(EWeaponType WeaponType);

  /** Ammo counter **/
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
  int AmmoAmount;

  /** Max ammo amount **/
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
  int MaxAmmoAmount = 100;

  /** Getter for the uint32 **/
  UFUNCTION(BlueprintCallable, Category = Weapon)
  int GetAmmoAmount();

  /** Getter for the uint32 **/
  UFUNCTION(BlueprintCallable, Category = Weapon)
  int GetMaxAmmoAmount();

  /** Add ammo to character inventory **/
  UFUNCTION(BlueprintCallable, Category = Weapon)
  void AddAmmo(int AdditionAmmoAmount);

  /** try to consume ammo from character inventory **/
  UFUNCTION(BlueprintCallable, Category = Weapon)
  bool TryToConsumeAmmo(int RequestedAmmoAmount);

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
  TMap<EWeaponType, TSoftObjectPtr<UTP_WeaponComponent>> CachedWeapons;

  /** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

  /** Called for pause input */
  void Pause();

  /** Called for TakeRifleInHand input */
  void TakeRifleInHand();

  /** Called for TakeGrenadeInHand input */
  void TakeGrenadeInHand();

  /** */
  void UpdateWeaponUI(EWeaponType Weapontype);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
  /*
  * HUD
  */

  /** Widget class to spawn for the heads up display */
  UPROPERTY(EditAnywhere, Category = "Player HUD")
  TSubclassOf<class UPlayerHUD> PlayerHUDClass;

  /** The widget instance that we are use as our Hud */
  UPROPERTY()
  class UPlayerHUD* PlayerHUD;

  /** Widget class to spawn for the heads up display */
  UPROPERTY(EditAnywhere, Category = "Pause menu")
  TSubclassOf<class UPauseMenu> PauseMenuClass;

  /** The widget instance that we are use as our Hud */
  UPROPERTY()
  class UPauseMenu* PauseMenu;
};

