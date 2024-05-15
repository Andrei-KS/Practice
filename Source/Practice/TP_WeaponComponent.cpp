// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "PracticeCharacter.h"
#include "PracticeProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
  WeaponType = EWeaponType::None;

	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}


void UTP_WeaponComponent::Use()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
}

void UTP_WeaponComponent::AttachWeapon(APracticeCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr || Character->GetWeapon(WeaponType) != nullptr)
	{
		return;
	}

	// Attach the weapon to the First Person Character
  AttachWeaponToHand();
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetWeapon(this);

  // Set up action bindings
  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
    {
      // Fire
      EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Use);
    }
  }

  EnableWeapon();
}

void UTP_WeaponComponent::AttachWeaponToHand()
{
  if (Character == nullptr)
  {
    return;
  }

  FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
  AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
  SetVisibility(true,true);
}

void UTP_WeaponComponent::AttachWeaponToInventory()
{
  if (Character == nullptr)
  {
    return;
  }

  FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
  AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("InvetoryPoint")));
  SetVisibility(false, true);
}

void UTP_WeaponComponent::EnableWeapon()
{
  if (Character == nullptr || Character->GetWeapon(WeaponType) == nullptr)
  {
    return;
  }

  // Set up action mapping
  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      // Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
      Subsystem->AddMappingContext(UseMappingContext, 1);
    }
  }
}

void UTP_WeaponComponent::DisabaleWeapon()
{
  if (Character == nullptr)
  {
    return;
  }

  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      Subsystem->RemoveMappingContext(UseMappingContext);
    }
  }
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  DisabaleWeapon();
}