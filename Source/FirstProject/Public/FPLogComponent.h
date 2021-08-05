// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveWorldSubsystem.h"
#include "FPLogComponent.generated.h"

//Include this because we don't inherit from it?
class ATriggerBox;
class UBoxComponent;

UENUM()
enum class ECubeState
{
	CS_Waiting = 0  UMETA(DisplayName = "Waiting for jump"),
	CS_JumpedOn = 1 UMETA(DisplayName = "Jump complete"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPROJECT_API UFPLogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPLogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnJumpedOn();

	UPROPERTY(EditAnywhere)
	FString DataString;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CheckBox;

	UPROPERTY(BlueprintReadOnly)
	ECubeState CubeState;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
