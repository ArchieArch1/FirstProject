#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.generated.h"

UCLASS()

/*	Subystems have set lifetimes managed by Unreal. In this case, a world subsystem is destroyed when the world is deleted
	Setup the ObjectiveHere (C++ Class) here so ObjectiveWorldSubsystem has the responsibility of the ObjectiveWidget
	UObjectiveSubsystem <- UWorldSubsystem <- USubsystem <- UObject <- UObjectBaseUtility <- UObjectBase   */
		
/*	The ObjectiveWorldSubsystem handles all objectives in the world and the widget which displays the objective details
	Contains the array of objectives (stores them all)
	ObjectiveComponent gets a pointer to this WorldSubsystem so it can call the methods here for each objective when needed	*/
	
class FIRSTPROJECT_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	//Call back functions to create and display the ObjectiveWidget
	void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

	//This will search through the objectives array to find the information specific to the objective
	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	//Add a new objective (ObjectiveComponent instance)
	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);
	
	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

	//Broadcasted by StateChangedEvent in ObjectiveComponent when an objective state is changed
	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);

private:
	//Null pointer which will point to the objective widget
	UUserWidget* ObjectiveWidget = nullptr;

	//Add/remove them
	//Sign up for callback onchanged
	TArray<UObjectiveComponent*> Objectives;
};
