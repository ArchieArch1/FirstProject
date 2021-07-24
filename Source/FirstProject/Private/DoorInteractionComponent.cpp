// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

constexpr float FLT_METERS(float meters) { return meters * 100.0f; }

//Declare and define the debug console command
static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("FirstProject.DoorInteractionComponent.Debug"),
	false, TEXT("Toggle DoorInteractionComponent debug display."),
	ECVF_Default);

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DoorState = EDoorState::DS_Closed;

	//Log when the FirstProject.DoorInteractionComponent.Debug command has been toggled
	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorInteractionComponent::OnDebugToggled));
}

// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();	
	CurrentRotationTime = 0.0f;
	StartRotation = GetOwner()->GetActorRotation();
}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	//If the door is closed, and the box triggers, world and player can be found
	if (DoorState == EDoorState::DS_Closed)
	{
		if (BoxTriggerFront && BoxTriggerBack && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			//Setup pointer to the player pawn object
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			CurrentRotation = GetOwner()->GetActorRotation();

			//We need to know which direction the door is going to open, so check both front and back BoxTriggers
			if (PlayerPawn && BoxTriggerBack->IsOverlappingActor(PlayerPawn))
			{
				DoorState = EDoorState::DS_OpeningForwards;
				CurrentRotationTime = 0.0f; //Experiment with removing these after
			}

			else if (PlayerPawn && BoxTriggerFront->IsOverlappingActor(PlayerPawn))
			{
				DoorState = EDoorState::DS_OpeningBackwards;
				CurrentRotationTime = 0.0f; //Experiment with removing these after
			}
		}
	}

	//If the door state is opening (any direction)
	else if (DoorState == EDoorState::DS_OpeningForwards || DoorState == EDoorState::DS_OpeningBackwards)
	{
		//Use Delta Time
		CurrentRotationTime += DeltaTime;

		//Calculate AlphaRotation using FMath::Clamp method
		const float AlphaRotation = FMath::Clamp(CurrentRotationTime / TimeToRotate, CurrentRotationTime, TimeToRotate);

		//Choose lerp to use based on door direction
		if (DoorState == EDoorState::DS_OpeningForwards)
		{
			//Use returned value from FMath::Lerp to update actor rotation
			FRotator NewRotation = FMath::Lerp(StartRotation, FrontRotation, AlphaRotation);
			GetOwner()->SetActorRotation(NewRotation);
		}

		else if (DoorState == EDoorState::DS_OpeningBackwards)
		{
			//Use returned value from FMath::Lerp to update actor rotation
			FRotator NewRotation = FMath::Lerp(StartRotation, BackRotation, AlphaRotation);
			GetOwner()->SetActorRotation(NewRotation);
		}

		if (CurrentRotationTime >= 1.0f)
		{
			DoorState = EDoorState::DS_Open;
		}
	}

	//If door is open, it can close if the player is outside of the box triggers
	else if (DoorState == EDoorState::DS_Open)
	{
		//Set current rotation so door position can be identified. Get the player pawn again as it is out of scope
		CurrentRotation = GetOwner()->GetActorRotation();		
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

		//If the player is outside of both triggers and the alpha is greater than 0, close door
		if (!BoxTriggerFront->IsOverlappingActor(PlayerPawn) && !BoxTriggerBack->IsOverlappingActor(PlayerPawn) && CurrentRotationTime >= 0)
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
			}

			if (CurrentRotation.Yaw < StartRotation.Yaw)
			{
				//Close forwards
				CurrentRotationTime -= DeltaTime;
				const float AlphaRotation = FMath::Clamp(CurrentRotationTime / TimeToRotate, CurrentRotationTime, TimeToRotate);

				FRotator NewRotation = FMath::Lerp(StartRotation, BackRotation, AlphaRotation);
				GetOwner()->SetActorRotation(NewRotation);
			}

			//If door is closed, update state and reset CurrentRotation vector
			if (CurrentRotationTime <= 0)
			{
				DoorState = EDoorState::DS_Closed;
				CurrentRotation = FRotator::ZeroRotator;
			}
		}
	}

	DebugDraw();
}

//Log when the FirstProject.DoorInteractionComponent.Debug command has been toggled
void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable* Var)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

//Display the debug output above the door actor
void UDoorInteractionComponent::DebugDraw()
{
	if (CVarToggleDebugDoor->GetBool())
	{
		//Create offset value for the debug draw positioning
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;

		//Output door state into world
		FString EnumAsString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}


