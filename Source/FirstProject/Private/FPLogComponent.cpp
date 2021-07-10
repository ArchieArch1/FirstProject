// Fill out your copyright notice in the Description page of Project Settings.


#include "FPLogComponent.h"

// Sets default values for this component's properties
UFPLogComponent::UFPLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Error, TEXT("FP Component Created"));
}

// Called when the game starts
void UFPLogComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("UFPLogComponent::BeginPlay() %s"), *DataString);		
}

// Called every frame
void UFPLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

