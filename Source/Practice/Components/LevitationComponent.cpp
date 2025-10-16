// Fill out your copyright notice in the Description page of Project Settings.


#include "LevitationComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULevitationComponent::ULevitationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULevitationComponent::BeginPlay()
{
	Super::BeginPlay();
  if (bIsLevitationComponetEnabled)
  {
    FString ownerName = this->GetOwner()->GetName();
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("%s use bIsLevitationComponetEnabled = %d and LevitationHeightOfLevitationComponet = %.2f in ULevitationComponent::TickComponent"), *ownerName, bIsLevitationComponetEnabled, LevitationHeightOfLevitationComponet));
    OwnerMesh = this->GetOwner()->GetComponentByClass<UStaticMeshComponent>();
  }
}

PRAGMA_DISABLE_OPTIMIZATION
// Called every frame
void ULevitationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  if (bIsLevitationComponetEnabled && IsValid(OwnerMesh))
  {
    AActor* owner = this->GetOwner();
    // Set what actors to seek out from it's collision channel
    TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
    traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
    // Ignore any specific actors
    TArray<AActor*> ignoreActors;
    // Ignore self or remove this line to not ignore any
    ignoreActors.Init(owner, 1);
    // Sphere's spawn loccation within the world
    FVector startLocation = owner->GetActorLocation();
    FVector endLocation = startLocation - FVector::UpVector * LevitationHeightOfLevitationComponet;
    //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("startLocation = %f, endLocation = %f"), startLocation.Z, endLocation.Z));
    FHitResult OutHit;

    if (UKismetSystemLibrary::LineTraceSingle(
      GetWorld(),
      startLocation,
      endLocation,
      ETraceTypeQuery::TraceTypeQuery1,
      false,
      ignoreActors,
      EDrawDebugTrace::Persistent,
      OutHit,
      true
    ))
    {
      float reflexiveForce = OwnerMesh->GetMass() * 1000;
      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("reflexiveForce = %f"), reflexiveForce));
      OwnerMesh->AddForce(FVector(0, 0, reflexiveForce));
    }
    else
    {
      float reflexiveForce = OwnerMesh->GetMass() * 950;
      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("reflexiveForce = %f"), reflexiveForce));
      OwnerMesh->AddForce(FVector(0, 0, reflexiveForce));
    }
  }
}
PRAGMA_ENABLE_OPTIMIZATION

