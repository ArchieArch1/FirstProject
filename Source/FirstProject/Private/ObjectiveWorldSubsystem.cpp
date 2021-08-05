// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectiveWorldSubsystem.h"
#include "ObjectiveComponent.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
{
	//If the pointer to the objective widget is null, create a new objective widget and point to it
	if (ObjectiveWidget == nullptr)
	{
		//Get the player contoller inside the world
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		//Create new Widget object by passing in the UUserWidget SubClass type, Playercontroller and ObjectiveWidgetClass. 
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	//Don't use DisplayObjectiveWidget if there is no objective widget
	ensureMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSubsystem::DisplayObjectiveWidget ObjectiveWidget is nullptr"));
	ObjectiveWidget->AddToViewport();
}

//Get the details of the objective so the widget knows what to display
FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	//If there are no objectives in the array, display N/A
	if (!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive)
	{
		return TEXT("N/A");
	}

	//We always get the first element in objectives, I need to expand on this logic to display multiple objectives/active objectives etc (what is relevant to the player)
	//Work out how to get the desired ObjectiveDescrition here to check against in the array
	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed)
	{
		RetObjective += TEXT(" Completed!");
	}

	return RetObjective;
}

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComponent* ObjectiveComponent)
{
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);

	if (Objectives.Num() > PrevSize)
	{
		/*	Binding FStateChanged event delegate to ObjectiveStateChanged when the objective is first added			
			When OnStateChanged calls broadcast, we will call our function on objective state changed	*/
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComponent* ObjectiveComponent)
{
	Objectives.Remove(ObjectiveComponent);
}

//When an objective state is changed, display the widget using the details from the objective component passed in
void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState)
{
	DisplayObjectiveWidget();
}