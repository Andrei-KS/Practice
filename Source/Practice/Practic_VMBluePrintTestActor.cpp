// Fill out your copyright notice in the Description page of Project Settings.


#include "Practic_VMBluePrintTestActor.h"

// Sets default values
APractic_VMBluePrintTestActor::APractic_VMBluePrintTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APractic_VMBluePrintTestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APractic_VMBluePrintTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

