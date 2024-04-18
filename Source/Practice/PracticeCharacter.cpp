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

#include "EventBusSubsystem/BusSubsystemEvent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APracticeCharacter

APracticeCharacter::APracticeCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
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
    // TODO: add UpdateWeaponUI()
    TObjectPtr<UWeaponUIBusSubsystemEvent> eventWUIBE = UBusSubsystemEvent::Make<UWeaponUIBusSubsystemEvent>(this);
    eventWUIBE->Send();
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
    EnhancedInputComponent->BindAction(TakeRiflInHandAction, ETriggerEvent::Triggered, this, &APracticeCharacter::TakeRiflInHand);
    
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

void APracticeCharacter::TakeRiflInHand()
{
  if (!bHasRifle && CachedRifle.IsValid())
  {
    bHasRifle = true;
    CachedRifle->AttachWeaponToHand();
    CachedRifle->EnableWeapon();
    if (IsValid(PlayerHUD))
    {
      // TODO: add UpdateWeaponUI()
      TObjectPtr<UWeaponUIBusSubsystemEvent> eventWUIBE = UBusSubsystemEvent::Make<UWeaponUIBusSubsystemEvent>(this);
      eventWUIBE->WeaponType = EWeaponType::Rifle;
      eventWUIBE->AmmoAmount = AmmoAmount;
      eventWUIBE->MaxAmmoAmount = MaxAmmoAmount;
      eventWUIBE->Send();
    }
  }
}

void APracticeCharacter::TakeGrenadeInHand()
{
  if (bHasRifle && CachedRifle.IsValid())
  {
    bHasRifle = false;
    CachedRifle->AttachWeaponToInventory();
    CachedRifle->DisabaleWeapon();
  }

  if (IsValid(PlayerHUD))
  {
    // TODO: add UpdateWeaponUI()
    TObjectPtr<UWeaponUIBusSubsystemEvent> eventWUIBE = UBusSubsystemEvent::Make<UWeaponUIBusSubsystemEvent>(this);
    eventWUIBE.Get()->WeaponType = EWeaponType::Grenade;
    eventWUIBE.Get()->Send();
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("APracticeCharacter::BeginPlay made eventWUIBE of %d"), eventWUIBE->GetEventType()));
  }
}

void APracticeCharacter::UpdateWeaponUI()
{
  //TODO: need to add possibility work with different EWeaponType
  TObjectPtr<UWeaponUIBusSubsystemEvent> eventWUIBE = UBusSubsystemEvent::Make<UWeaponUIBusSubsystemEvent>(this);
  eventWUIBE->WeaponType = EWeaponType::Rifle;
  eventWUIBE->AmmoAmount = AmmoAmount;
  eventWUIBE->MaxAmmoAmount = MaxAmmoAmount;
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

void APracticeCharacter::SetRifle(UTP_WeaponComponent* NewRifle)
{
  bHasRifle = true;
  CachedRifle = NewRifle;
  if (IsValid(PlayerHUD))
  {
    UpdateWeaponUI();
  }
}

UTP_WeaponComponent* APracticeCharacter::GetRifle()
{
	return CachedRifle.Get();
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

  if (IsValid(PlayerHUD) && CachedRifle.IsValid())
  {
    UpdateWeaponUI();
  }

  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("APracticeCharacter::AddAmmo. AdditionAmmoAmount %d, in inventary %d"), AdditionAmmoAmount, AmmoAmount));
}

bool APracticeCharacter::TryToConsumeAmmo(int RequestedAmmoAmount)
{
  // If the character has enough ammo, the requested ammo amount will be consumed
  if (RequestedAmmoAmount <= AmmoAmount)
  {
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("APracticeCharacter::TryToConsumeAmmo consume %d ammo, remmanig %d ammo"), RequestedAmmoAmount, AmmoAmount));
    AmmoAmount -= RequestedAmmoAmount;
    if (IsValid(PlayerHUD))
    {
      UpdateWeaponUI();
    }
    return true;
  }

  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("APracticeCharacter::TryToConsumeAmmo can't consume %d ammo, remmanig %d ammo"), RequestedAmmoAmount, AmmoAmount));
  return false;
}