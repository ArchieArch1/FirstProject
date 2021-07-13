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
}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
	if (CurrentRotationTime <= TimeToRotate)
	{
		if (TriggerBoxBack && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			
			//If Pawn & TriggerBox overlap, door is opening 			
			if (PlayerPawn && TriggerBoxBack->IsOverlappingActor(PlayerPawn))
			{
				//Add Delta time to Alpha for Lerp
				CurrentRotationTime += DeltaTime;

				//Get the alpha position (between 0 and 1) using Clamp
				const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);

				//Use Linear Interpolation (Lerp) to rotate the actor
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, DesiredRotationFront, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);

				//Round back down to 10 if CurrentRotationTime because greater than TimeToRotate
				if (CurrentRotationTime > TimeToRotate)
				{
					CurrentRotationTime = FMath::Floor(CurrentRotationTime);
				}
			}

			else if (PlayerPawn && TriggerBoxFront->IsOverlappingActor(PlayerPawn))
			{
				UE_LOG(LogTemp, Warning, TEXT("1"));
				//Add Delta time to Alpha for Lerp
				CurrentRotationTime += DeltaTime;

				//Get the alpha position (between 0 and 1) using Clamp
				const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);

				//Use Linear Interpolation (Lerp) to rotate the actor
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, DesiredRotationBack, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);

				//Round back down to 10 if CurrentRotationTime because greater than TimeToRotate
				if (CurrentRotationTime > TimeToRotate)
				{
					CurrentRotationTime = FMath::Floor(CurrentRotationTime);
				}
			}

			//If Player is outside of TriggerBox and Alpha is greater than 0, door is closing			
			if (PlayerPawn && !TriggerBoxBack->IsOverlappingActor(PlayerPawn) && CurrentRotationTime > 0)
			{
				//Subtract delta time from Alpha instead
				CurrentRotationTime -= DeltaTime;

				const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);

				const FRotator CurrentRotation = FMath::Lerp(StartRotation, DesiredRotationFront, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);				
			}
		}
	}
}


