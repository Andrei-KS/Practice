// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
  None = 0,
  Physical,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

  UFUNCTION(BlueprintCallable)
  void ApplyDamageTo(AActor* target);

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
  EDamageType DamageType = EDamageType::Physical;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
  int DamageValue = 10;
};
