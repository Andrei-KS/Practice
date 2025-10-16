// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeCharacter.h"
#include "PracticePlayerController.h"
#include "PracticeProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "UI/PlayerHUD.h"
#include "UI/PauseMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TP_WeaponComponent.h"
#include "Practic_GrenadeComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SplineComponent.h"


#include "EventBusSubsystem/BusSubsystemEvent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APracticeCharacter

APracticeCharacter::APracticeCharacter()
{
  CurrentWeaponTypeInHand = EWeaponType::None;

	// Character doesn`t have a rifle at start
  bIsRifleInHand = false;
	
  // Character doesnt have a ammo at start
  AmmoAmount = 0;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

  // HUD
  PlayerHUDClass = nullptr;
  PlayerHUD = nullptr;

  //PredictProjectilePath
  PredictProjectilePathSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PredictProjectilePathSplineComponent"));
  PredictProjectilePathSplineComponent->SetupAttachment(GetRootComponent());
  PredictProjectilePathSplineComponent->SetHiddenInGame(true, true);

  PredictProjectilePathVisualEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PredictProjectilePathVisualEffect"));
  PredictProjectilePathVisualEffect->SetupAttachment(PredictProjectilePathSplineComponent);
  bIsCalculatePredictProjectilePath = false;
  PredictLaunchVelocity = 0;
  ProjectileRadius = 20;
}

void APracticeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

  // HUD
  if (IsLocallyControlled() && PlayerHUDClass)
  {
    // for local player controller
    APracticePlayerController* PPC = GetController<APracticePlayerController>();
    check(PPC);
    PlayerHUD = CreateWidget<UPlayerHUD>(PPC, PlayerHUDClass);
    check(PlayerHUD);
    PlayerHUD->AddToPlayerScreen();
    UpdateWeaponUI(EWeaponType::None);
  }
}

void APracticeCharacter::Tick(float DeltaSecond)
{
  Super::Tick(DeltaSecond);
  if (bIsCalculatePredictProjectilePath && CurrentWeaponTypeInHand != EWeaponType::None)
  {
    PredictProjectilePathSplineComponent->SetVisibility(true, true);
    FPredictProjectilePathParams PredictParams;
    TSoftObjectPtr<UTP_WeaponComponent> pWeaponComponent = CachedWeapons[CurrentWeaponTypeInHand];
    FProjectileSpawnProperty PSProperty = pWeaponComponent->GetProjectileSpawnProperty();
    PredictParams.StartLocation = PSProperty.SpawnLocation;
    PredictParams.LaunchVelocity = PSProperty.SpawnRotation.Vector() * PredictLaunchVelocity;
    PredictParams.ProjectileRadius = ProjectileRadius;
    FPredictProjectilePathResult PredictResult;
    bool bHit = UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult);

    TArray<FVector> PointLocation;
    for (auto PathPoint : PredictResult.PathData)
    {
      PointLocation.Add(PathPoint.Location);
    }

    PredictProjectilePathSplineComponent->SetSplinePoints(PointLocation,ESplineCoordinateSpace::World);
  }
  else
  {
    PredictProjectilePathSplineComponent->SetVisibility(false, true);
  }
}

void APracticeCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  if (IsValid(PlayerHUD))
  {
    PlayerHUD->RemoveFromParent();
    // We can't destroy the widget directly, let the GC take care of it
    PlayerHUD = nullptr;
  }

  // Call the base class  
  Super::EndPlay(EndPlayReason);
}

//////////////////////////////////////////////////////////////////////////// Input

void APracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APracticeCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APracticeCharacter::Look);

    // Pause
    EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APracticeCharacter::Pause);
    
    // TakeRiflInHand
    EnhancedInputComponent->BindAction(TakeRiflInHandAction, ETriggerEvent::Triggered, this, &APracticeCharacter::TakeRifleInHand);
    
    // TakeGrenadeInHand
    EnhancedInputComponent->BindAction(TakeGrenadeInHandAction, ETriggerEvent::Triggered, this, &APracticeCharacter::TakeGrenadeInHand);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void APracticeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APracticeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APracticeCharacter::TakeRifleInHand()
{
  TakeWeaponInHand(EWeaponType::Rifle);
}

void APracticeCharacter::TakeGrenadeInHand()
{
  TakeWeaponInHand(EWeaponType::Grenade);
}

void APracticeCharacter::TakeWeaponInHand(EWeaponType weaponType)
{
  if (CurrentWeaponTypeInHand == weaponType)
  {
    return;
  }

  HideWeapon(CurrentWeaponTypeInHand);

  if (!CachedWeapons.Contains(weaponType))
  {
    return;
  }

  TSoftObjectPtr<UTP_WeaponComponent> pWeaponComponent = CachedWeapons[weaponType];
  pWeaponComponent->AttachWeaponToHand();
  pWeaponComponent->EnableWeapon();

  if (IsValid(PlayerHUD))
  {
    UpdateWeaponUI(weaponType);
  }

  CurrentWeaponTypeInHand = weaponType;

  switch (weaponType)
  {
  case EWeaponType::Rifle:
  {
    bIsRifleInHand = true;
    //FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
    //PredictProjectilePathSplineComponent->AttachToComponent(pWeaponComponent.Get(), AttachmentRules,FName(TEXT("Muzzle")));
    //PredictProjectilePathSplineComponent->SetHiddenInGame(false, true);
    PredictLaunchVelocity = 3000;
    ProjectileRadius = 20;
    bIsCalculatePredictProjectilePath = true;
  }
  break;
  case EWeaponType::Grenade:
  {
    //FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
    //PredictProjectilePathSplineComponent->AttachToComponent(pWeaponComponent.Get(), AttachmentRules, FName(TEXT("Muzzle")));
    //PredictProjectilePathSplineComponent->SetHiddenInGame(false, true);
    PredictLaunchVelocity = 500;
    ProjectileRadius = 10;
    bIsCalculatePredictProjectilePath = true;
  }
  break;
  }


}

void APracticeCharacter::HideWeapon(EWeaponType Weapontype)
{
  if (CachedWeapons.Contains(Weapontype))
  {
    TSoftObjectPtr<UTP_WeaponComponent> Weapon = CachedWeapons[Weapontype];
    Weapon->AttachWeaponToInventory();
    Weapon->DisabaleWeapon();

    if (CurrentWeaponTypeInHand == EWeaponType::Grenade)
    {
      PredictProjectilePathSplineComponent->ClearSplinePoints();
    }

    CurrentWeaponTypeInHand = EWeaponType::None;
    UpdateWeaponUI(EWeaponType::None);
    bIsRifleInHand = false;
  }
}

void APracticeCharacter::UpdateWeaponUI(EWeaponType Weapontype)
{
  TObjectPtr<UWeaponUIBusSubsystemEvent> eventWUIBE = UBusSubsystemEvent::Make<UWeaponUIBusSubsystemEvent>(this);
  eventWUIBE->WeaponType = Weapontype;
  switch (Weapontype)
  {
  case EWeaponType::None:
    break;
  case EWeaponType::Rifle:
    eventWUIBE->AmmoAmount = AmmoAmount;
    eventWUIBE->MaxAmmoAmount = MaxAmmoAmount;
    break;
  case EWeaponType::Grenade:
    break;
  default:
    break;
  }

  eventWUIBE->Send();
  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("APracticeCharacter::BeginPlay made eventWUIBE of %d"), eventWUIBE->GetEventType()));
}

void APracticeCharacter::Pause()
{
  if (!UGameplayStatics::IsGamePaused(GetWorld()))
  {
    // for local player controller
    APracticePlayerController* PPC = GetController<APracticePlayerController>();
    check(PPC);
    PauseMenu = CreateWidget<UPauseMenu>(PPC, PauseMenuClass);
    check(PauseMenu);
    PauseMenu->AddToPlayerScreen();
    UGameplayStatics::SetGamePaused(GetWorld(), true);
    FInputModeGameAndUI InputModeGameAndUI;
    PPC->SetInputMode(InputModeGameAndUI);
    PPC->SetShowMouseCursor(true);
  }
}

void APracticeCharacter::SetWeapon(UTP_WeaponComponent* NewWeapon)
{
  if (NewWeapon == nullptr)
  {
    return;
  }

  if (CachedWeapons.Contains(NewWeapon->GetWeaponType()))
  {
    return;
  }

  CachedWeapons.Add(NewWeapon->GetWeaponType(), NewWeapon);
  TakeWeaponInHand(NewWeapon->GetWeaponType());
}

UTP_WeaponComponent* APracticeCharacter::GetWeapon(EWeaponType WeaponType)
{
  if (CachedWeapons.Contains(WeaponType))
  {
    return CachedWeapons[WeaponType].Get();
  }
	return nullptr;
}

int APracticeCharacter::GetAmmoAmount()
{
  return AmmoAmount;
}

int APracticeCharacter::GetMaxAmmoAmount()
{
  return MaxAmmoAmount;
}

void APracticeCharacter::AddAmmo(int AdditionAmmoAmount)
{
  GetGameInstance();
  AmmoAmount += AdditionAmmoAmount;
  if (AmmoAmount > MaxAmmoAmount)
  {
    AmmoAmount = MaxAmmoAmount;
  }

  if (IsValid(PlayerHUD) && CachedWeapons.Contains(EWeaponType::Rifle))
  {
    UpdateWeaponUI(EWeaponType::Rifle);
  }

  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("APracticeCharacter::AddAmmo. AdditionAmmoAmount %d, in inventary %d"), AdditionAmmoAmount, AmmoAmount));
}

bool APracticeCharacter::TryToConsumeAmmo(int RequestedAmmoAmount)
{
  if (MyConsoleVariable::bIsInfiniteRifleAmmo.GetValueOnGameThread() && CurrentWeaponTypeInHand == EWeaponType::Rifle)
  {
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("APracticeCharacter::TryToConsumeAmmo Granted infinity ammo"), RequestedAmmoAmount, AmmoAmount));
    return true;
  }

  // If the character has enough ammo, the requested ammo amount will be consumed
  if (RequestedAmmoAmount <= AmmoAmount)
  {
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("APracticeCharacter::TryToConsumeAmmo consume %d ammo, remmanig %d ammo"), RequestedAmmoAmount, AmmoAmount));
    AmmoAmount -= RequestedAmmoAmount;
    if (IsValid(PlayerHUD))
    {
      UpdateWeaponUI(EWeaponType::Rifle);
    }
    return true;
  }

  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("APracticeCharacter::TryToConsumeAmmo can't consume %d ammo, remmanig %d ammo"), RequestedAmmoAmount, AmmoAmount));
  return false;
}