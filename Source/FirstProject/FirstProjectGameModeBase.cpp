// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstProjectGameModeBase.h"
#include "ObjectiveWorldSubsystem.h"

void AFirstProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	//Create a pointer to the ObjectiveWorldSubsystem (ObjectiveWorldSubsystem.h & ObjectiveWorldSubsystem.cpp)
	//We need to do this as we are dealing with objects which are responsible for the objective state, they are stored in the ObjectiveWorldSubsystem
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();

	if (ObjectiveWorldSubsystem)
	{
		//Call back functions to create and display the objective widget
		//CreateObjectiveWidget calls UUserWidge::*CreateWidget, this is why the widget object created in the gameloop doesn't need to be a pointer/ref
		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();		
	}
}

