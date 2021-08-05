// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "ObjectiveWorldSubsystem.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;

//Door States for debugging
UENUM()
enum class EDoorState
{
	DS_Closed = 0 UMETA(DisplayName = "Closed"),
	DS_Open = 1 UMETA(DisplayName = "Open"),
	DS_OpeningForwards = 2 UMETA(DisplayName = "Opening Forwards"),
	DS_OpeningBackwards = 3 UMETA(DisplayName = "Opening Backwards"),
	DS_Locked = 4 UMETA(DisplayName = "Locked")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPROJECT_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//********** Declare OpenedEvent ********** 
	/*	Declare the event (multi-class delegate). 
		The owning type (FDoorInteractionComponent) is the only type which will have access to invoke the Event Broadcast, IsBounce and Clear functions
		This event/multi-cast delegate will be binded to the ObjectiveWorldSubsystem (the UObject)
		There can be multiple events using the FOpened type, so OpenedEvent is actually an object/variant?	*/

	DECLARE_EVENT(FDoorInteractionComponent, FOpened)

	//Declare internal member variable. This is used 
	FOpened OpenedEvent;	

	//Callback function signature. Not sure what this is used for yet.
	FOpened& OnOpened() { return OpenedEvent; }

	void OnDoorOpen();
	static void OnDebugToggled(IConsoleVariable* Var);
	void DebugDraw();
	void Test(float delta);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	UPROPERTY(EditAnywhere)
	float TimeToRotate;
	float CurrentRotationTime;
	
	UPROPERTY(EditAnywhere)
	FRotator FrontRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	FRotator BackRotation = FRotator::ZeroRotator;
	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator CurrentRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	ATriggerBox* BoxTriggerFront;

	UPROPERTY(EditAnywhere)
	ATriggerBox* BoxTriggerBack;

	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState;
};
