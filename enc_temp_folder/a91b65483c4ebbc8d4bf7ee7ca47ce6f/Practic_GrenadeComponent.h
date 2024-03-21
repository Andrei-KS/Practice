// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Practic_GrenadeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UPractic_GrenadeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
  /** Projectile class to spawn */
  UPROPERTY(EditDefaultsOnly, Category = Projectile)
  TSubclassOf<class APracticeProjectile> ProjectileClass;

  /** MappingContext */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputMappingContext* FireMappingContext;

  /** Throw Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* ThrowAction;

	// Sets default values for this component's properties
	UPractic_GrenadeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
