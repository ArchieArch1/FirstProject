// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "FirstProjectGameModeBase.generated.h"

UCLASS()
class FIRSTPROJECT_API AFirstProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void StartPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;

	UUserWidget* ObjectiveWidget = nullptr;
};
