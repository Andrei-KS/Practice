// Fill out your copyright notice in the Description page of Project Settings.


#include "TraveledPath.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ATraveledPath::ATraveledPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  TraveledPathSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("TraveledPathSplineComponent"));
  RootComponent = TraveledPathSplineComponent;

  TraveledPathVisualEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TraveledPathVisualEffect"));
  TraveledPathVisualEffect->SetupAttachment(TraveledPathSplineComponent);
}

// Called when the game starts or when spawned
void ATraveledPath::BeginPlay()
{
	Super::BeginPlay();
  TraveledPathSplineComponent->ClearSplinePoints(true);
	
}

// Called every frame
void ATraveledPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

