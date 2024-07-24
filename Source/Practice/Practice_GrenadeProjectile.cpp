// Fill out your copyright notice in the Description page of Project Settings.


#include "Practice_GrenadeProjectile.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/DamageComponent.h"
#include "Components/SplineComponent.h"

APractice_GrenadeProjectile::APractice_GrenadeProjectile()
{
  InitialLifeSpan = 0.0f;
  ExplotionRadius = 50.0f;
  FuseLenght = 5.0f;

  // Use DamageComponent to applay damage to other actor that contain health component
  ExplodionDamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("ExplodionDamageComponent"));

  TraveledPathSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("TraveledPathSplineComponent"));
  TraveledPathSplineComponent->SetupAttachment(RootComponent);

  TraveledPathVisualEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TraveledPathVisualEffect"));
  TraveledPathVisualEffect->SetupAttachment(TraveledPathSplineComponent);
}

void APractice_GrenadeProjectile::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);
  FVector newPosition = GetCollisionComp()->GetComponentLocation();
  if (TraveledPath.IsEmpty() || newPosition != TraveledPath.Last())
  {
    TraveledPath.Push(newPosition);
    TraveledPathSplineComponent->SetSplinePoints(TraveledPath, ESplineCoordinateSpace::World);

    // I don't understand why function AddSplinePoint and Vector(0,0,0), this spline is invalid
    //TraveledPathSplineComponent->AddSplinePoint(GetCollisionComp()->GetComponentLocation(),ESplineCoordinateSpace::World);
  }
  
}

void APractice_GrenadeProjectile::BeginPlay()
{
  Super::BeginPlay();
  FTimerHandle TExplodeHandle;
  GetWorldTimerManager().SetTimer(TExplodeHandle, this, &APractice_GrenadeProjectile::Explode, FuseLenght, false);
}

void APractice_GrenadeProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void APractice_GrenadeProjectile::Explode()
{
  // Set what actors to seek out from it's collision channel
  TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
  traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

  // Ignore any specific actors
  TArray<AActor*> ignoreActors;
  // Ignore self or remove this line to not ignore any
  ignoreActors.Init(this, 1);

  // Array of actors that are inside the radius of the sphere
  TArray<AActor*> outActors;

  // Sphere's spawn loccation within the world
  FVector sphereSpawnLocation = GetActorLocation();
  UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereSpawnLocation, ExplotionRadius, traceObjectTypes, NULL, ignoreActors, outActors);

  // Optional: Use to have a visual representation of the SphereOverlapActors
  DrawDebugSphere(GetWorld(), GetActorLocation(), ExplotionRadius, 12, FColor::Red, false, 5.0f);

  // Finally iterate over the outActor array
  for (AActor* overlappedActor : outActors) {
    UE_LOG(LogTemp, Warning, TEXT("Exploded an Actor: %s"), *overlappedActor->GetName());
    ExplodionDamageComponent->ApplyDamageTo(overlappedActor);
  }

  Destroy();
}
