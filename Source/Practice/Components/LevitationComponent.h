// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevitationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), config=Game )
class PRACTICE_API ULevitationComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  ULevitationComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
  TObjectPtr<UStaticMeshComponent> OwnerMesh;

  UPROPERTY(Config)
  bool bIsLevitationComponetEnabled;

  UPROPERTY(Config)
  float LevitationHeightOfLevitationComponet;
};
