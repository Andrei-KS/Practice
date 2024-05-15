// Fill out your copyright notice in the Description page of Project Settings.


#include "Practic_RifleComponent.h"
#include "PracticeCharacter.h"
#include "PracticeProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UPractic_RifleComponent::UPractic_RifleComponent()
{
  WeaponType = EWeaponType::Rifle;

  // Default offset from the character location for projectiles to spawn
  MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}


void UPractic_RifleComponent::Use()
{
  Super::Use();
  if (!Character->TryToConsumeAmmo(1))
  {
    return;
  }

  // Try and fire a projectile
  if (ProjectileClass != nullptr)
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
      World->SpawnActor<APracticeProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
    }
  }

  // Try and play the sound if specified
  if (UseSound != nullptr)
  {
    UGameplayStatics::PlaySoundAtLocation(this, UseSound, Character->GetActorLocation());
  }

  // Try and play a firing animation if specified
  if (UseAnimation != nullptr)
  {
    // Get the animation object for the arms mesh
    UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
    if (AnimInstance != nullptr)
    {
      AnimInstance->Montage_Play(UseAnimation, 1.f);
    }
  }
}


