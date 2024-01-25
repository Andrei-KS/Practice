// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoComponent.generated.h"

class APracticeCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAmmoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
  int AmmoAmount = 10;

public:
  /** Get Ammo */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  void PickedUpBy(APracticeCharacter* TargetCharacter);
};
