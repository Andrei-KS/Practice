// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraveledPath.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UDamageComponent;
class USplineComponent;

UCLASS()
class PRACTICE_API ATraveledPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraveledPath();

  TObjectPtr<USplineComponent> GetTraveledPathSplineComponent() { return TraveledPathSplineComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere, Category = "TraveledPath")
  TObjectPtr<USplineComponent> TraveledPathSplineComponent;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraveledPath")
  TObjectPtr<UNiagaraComponent> TraveledPathVisualEffect;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraveledPath")
  UStaticMesh* SplaneMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
