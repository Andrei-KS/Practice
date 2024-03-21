// Fill out your copyright notice in the Description page of Project Settings.


#include "Practic_GrenadeComponent.h"
#include "PracticeCharacter.h"
#include "Practice_GrenadeProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UPractic_GrenadeComponent::UPractic_GrenadeComponent()
{
  // Default offset from the character location for projectiles to spawn
  MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UPractic_GrenadeComponent::Throw()
{
  if (Character == nullptr || Character->GetController() == nullptr)
  {
    return;
  }

  // Try and throw a projectile
  if (GrenadeProjectileClass != nullptr)
  {
    UWorld* const World = GetWorld();
    if (World != nullptr)
    {
      APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
      const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
      // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
      const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

      //Set Spawn Collision Handling Override
      FActorSpawnParameters ActorSpawnParams;
      ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

      // Spawn the projectile at the muzzle
      World->SpawnActor<APractice_GrenadeProjectile>(GrenadeProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
    }
  }
}

void UPractic_GrenadeComponent::AttachWeapon(APracticeCharacter* TargetCharacter)
{
  Character = TargetCharacter;

  // Check that the character is valid, and has no rifle yet
  if (Character == nullptr || Character->GetRifle() != nullptr)
  {
    return;
  }

  // Attach the weapon to the First Person Character
  AttachWeaponToHand();

  // switch bHasRifle so the animation blueprint can switch to another animation set
  //Character->SetRifle(this);

  // Set up action bindings
  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
    {
      // Throw
      EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &UPractic_GrenadeComponent::Throw);
    }
  }
}

void UPractic_GrenadeComponent::AttachWeaponToHand()
{
  if (Character == nullptr)
  {
    return;
  }

  FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
  AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripGrenadePoint")));
  SetVisibility(true, true);
}

void UPractic_GrenadeComponent::AttachWeaponToInventory()
{
  if (Character == nullptr)
  {
    return;
  }

  FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
  AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("InvetoryPoint")));
  SetVisibility(false, true);
}

void UPractic_GrenadeComponent::EnableWeapon()
{
  if (Character == nullptr || Character->GetRifle() == nullptr)
  {
    return;
  }

  // Set up action mapping
  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      // Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
      Subsystem->AddMappingContext(ThrowMappingContext, 1);
    }
  }
}

void UPractic_GrenadeComponent::DisabaleWeapon()
{
  if (Character == nullptr)
  {
    return;
  }

  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      Subsystem->RemoveMappingContext(ThrowMappingContext);
    }
  }
}

void UPractic_GrenadeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  DisabaleWeapon();
}