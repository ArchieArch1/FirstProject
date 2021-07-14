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
}

// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();	
	CurrentRotationTime = 0;
	StartRotation = GetOwner()->GetActorRotation();
}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
	
	//If the box triggers, world and player can be found
	if (BoxTriggerFront && BoxTriggerBack && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
	{
		//Setup player pawn and get the position of the door
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		CurrentRotation = GetOwner()->GetActorRotation();		

		//BoxTriggerFront collision detected and door is closed (allow 2 degrees for lerp overshooting)
		if (BoxTriggerFront->IsOverlappingActor(PlayerPawn) && CurrentRotation.Yaw <= (StartRotation.Yaw + 2))
		{
			//Use Delta Time
			CurrentRotationTime += DeltaTime;

			//Calculate AlphaRotation using FMath::Clamp method
			const float AlphaRotation = FMath::Clamp(CurrentRotationTime / TimeToRotate, CurrentRotationTime, TimeToRotate);

			//Use returned value from FMath::Lerp to update actor rotation
			FRotator NewRotation = FMath::Lerp(StartRotation, BackRotation, AlphaRotation);
			GetOwner()->SetActorRotation(NewRotation);

			if (CurrentRotationTime >= TimeToRotate)
			{
				CurrentRotationTime = FMath::Floor(CurrentRotationTime);
			}
		}		

		//BoxTriggerBack detected and door is closed (allow 2 degrees for lerp overshooting)
		else if (BoxTriggerBack->IsOverlappingActor(PlayerPawn) && CurrentRotation.Yaw >= (StartRotation.Yaw - 2))
		{
			//Use Delta Time
			CurrentRotationTime += DeltaTime;

			//Calculate AlphaRotation using FMath::Clamp method
			const float AlphaRotation = FMath::Clamp(CurrentRotationTime / TimeToRotate, CurrentRotationTime, TimeToRotate);

			//Use returned value from FMath::Lerp to update actor rotation
			FRotator NewRotation = FMath::Lerp(StartRotation, FrontRotation, AlphaRotation);
			GetOwner()->SetActorRotation(NewRotation);

			if (CurrentRotationTime >= TimeToRotate)
			{
				CurrentRotationTime = FMath::Floor(CurrentRotationTime);
			}
		}

		//If the player is outside of both triggers and the alpha is greater than 0, close door
		else if (!BoxTriggerFront->IsOverlappingActor(PlayerPawn) && !BoxTriggerBack->IsOverlappingActor(PlayerPawn) && CurrentRotationTime >= 0)
		{
			//Which direction does it need to close?
			if (CurrentRotation.Yaw > StartRotation.Yaw)
			{
				//Close backwards		
				//-= DeltaTime to do same lerp in reverse				
				CurrentRotationTime -= DeltaTime;
				const float AlphaRotation = FMath::Clamp(CurrentRotationTime / TimeToRotate, CurrentRotationTime, TimeToRotate);

				FRotator NewRotation = FMath::Lerp(StartRotation, FrontRotation, AlphaRotation);
				GetOwner()->SetActorRotation(NewRotation);

				if (CurrentRotation.Yaw == 0)
				{
					CurrentRotation.Yaw = FMath::Floor(CurrentRotation.Yaw);
				}
			}
			
			if (CurrentRotation.Yaw < StartRotation.Yaw)
			{		
				//Close forwards
				CurrentRotationTime -= DeltaTime;
				const float AlphaRotation = FMath::Clamp(CurrentRotationTime / TimeToRotate, CurrentRotationTime, TimeToRotate);

				FRotator NewRotation = FMath::Lerp(StartRotation, BackRotation, AlphaRotation);
				GetOwner()->SetActorRotation(NewRotation);

				if (CurrentRotation.Yaw == 0)
				{
					CurrentRotation.Yaw = FMath::Floor(CurrentRotation.Yaw);
				}
			}
		}
	}
}


