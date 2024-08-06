// Fill out your copyright notice in the Description page of Project Settings.


#include "Practic_GrenadeComponent.h"
#include "PracticeCharacter.h"
#include "PracticeProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SplineComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values for this component's properties
UPractic_GrenadeComponent::UPractic_GrenadeComponent()
{
  WeaponType = EWeaponType::Grenade;
  // Default offset from the character location for projectiles to spawn
  MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

  PredictedPathSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PredictedPathSplineComponent"));

  PredictedPathVisualEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PredictedPathVisualEffect"));
  
}

void UPractic_GrenadeComponent::AttachWeapon(APracticeCharacter* TargetCharacter)
{
  Super::AttachWeapon(TargetCharacter);

  SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
}

void UPractic_GrenadeComponent::Use()
{
  if (Character == nullptr || Character->GetController() == nullptr)
  {
    return;
  }

  // Try and throw a projectile
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
}
