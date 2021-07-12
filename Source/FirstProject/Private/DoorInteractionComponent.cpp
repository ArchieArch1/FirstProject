// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();	
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;	
	DoorState = false;
	//GetOwner()->SetActorRotation(DesiredRotation);
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (CurrentRotationTime <= TimeToRotate + 10)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			
			//If Pawn & TriggerBox overlap, door is opening 			
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				//Add Delta time to Alpha for Lerp
				CurrentRotationTime += DeltaTime;

				//Get the alpha position (between 0 and 1) using Clamp
				const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);

				//Use Linear Interpolation (Lerp) to rotate the actor
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);				
			}

			//If Player is outside of TriggerBox and Alpha is greater than 0, door is closing			
			if (PlayerPawn && !TriggerBox->IsOverlappingActor(PlayerPawn) && CurrentRotationTime > 0)
			{
				//Subtract delta time from Alpha instead
				CurrentRotationTime -= DeltaTime;

				const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);

				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);				
			}
		}
	}
}


