// Fill out your copyright notice in the Description page of Project Settings.

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
		
/*	The object responsible for the objective is ObjectiveWidget(type UUserWidget*, derived from UWidget)	
	The objective widget is created in the WorldSubsystem. Display and Create functions are also here
	UUserWidget <- UWidget <- UVisual <- UObject <- UObjectBaseUtility <- UObjectBase	*/
	
class FIRSTPROJECT_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	//Call back functions to create and display the ObjectiveWidget
	void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

	//This function is access in the widget blueprints
	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);

private:
	//Null pointer member of type UUserWidget
	UUserWidget* ObjectiveWidget = nullptr;

	//Add/remove them
	//Sign up for callback onchanged
	TArray<UObjectiveComponent*> Objectives;
};
