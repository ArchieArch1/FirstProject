// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPROJECT_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotationFront = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere)
	FRotator DesiredRotationBack = FRotator::ZeroRotator;
	FRotator StartRotation = FRotator::ZeroRotator;	

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;
	float CurrentRotationTime = 0.0f;	

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBoxBack;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBoxFront;
};
