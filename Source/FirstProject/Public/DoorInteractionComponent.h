// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;

//Door States for debugging
UENUM()
enum class EDoorState
{
	DS_Closed = 0 UMETA(DisplayName = "Closed"),
	DS_Open = 1 UMETA(DisplayName = "Open")
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
	static void OnDebugToggled(IConsoleVariable* Var);
	void DebugDraw();

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
