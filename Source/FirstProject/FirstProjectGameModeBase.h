// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "FirstProjectGameModeBase.generated.h"

UCLASS()

/*	FirstProjectGameModeBase is essentially the custom game loop. This is where the StartPlay function is used	
	We call the CreateObjectiveWidget and DisplayObjectiveWidget functions in the game loop	
	Although the ObjectiveWidget pointer and functions are setup in the ObjectiveWorldSubsystem, the object is created here after StartPlay	 */

class FIRSTPROJECT_API AFirstProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartPlay() override;

	/*	The objective widget class is setup through data in the case that we have different widgets(split screen or different levels etc)
		This allows us to data drive the object widget class
		The widget object is setup in the WorldSubsystem as it is responsible for the world objective	*/
	
	/*	Create the ObjectiveWidgetClass object used in the gameloop as any class type derived from UUserWidget (thanks to TSubclassOf)
		This is object is used as the parameter when UObjectiveWorldSystem::CreateObjectiveWidget is called at the beginning of the gameloop
		UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)	*/
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;		
};
