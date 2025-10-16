// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_EVENT(UMyClass, FDestroyAllThatHaveHealthComponentEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthOnDiedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthOnHitSignature, int, DamageValue);

namespace myConsoleCommand
{
  static FDestroyAllThatHaveHealthComponentEvent OnDestroyAllThatHaveHealthComponentEvent;
  static FAutoConsoleCommand ConsoleCommandName(
    TEXT("DestroyAllThatHaveHealthComponent"),
    TEXT("Description of the command"),
    FConsoleCommandDelegate::CreateLambda([]()
      {
        OnDestroyAllThatHaveHealthComponentEvent.Broadcast();
      })
  );
}


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

  UPROPERTY(BlueprintAssignable, Category = "Health")
  FHealthOnDiedSignature OnDied;

  UPROPERTY(BlueprintAssignable, Category = "Health")
  FHealthOnHitSignature OnHit;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
  bool bIsImmortal = false;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bIsImmortal == false"))
  int Health = 100;

public:
  UFUNCTION(BlueprintCallable, Category = "Health")
  void ApplyDamage(int DamageValue);

  void HandleDestroyAllThatHaveHealthComponentEvent();
};
