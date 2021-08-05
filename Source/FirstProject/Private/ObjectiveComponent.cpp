#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.h"

//Objective component constructor, sets default state but this is also done in the editor
UObjectiveComponent::UObjectiveComponent()
{	
	PrimaryComponentTick.bCanEverTick = false;
	State = EObjectiveState::OS_Inactive;
}

/*	Method to update the state on the objective component itself
	When a state is updated, it is broadcasted (the binded method in ObjectiveWorldSubsystem is called)	*/
void UObjectiveComponent::SetState(EObjectiveState NewState)
{
	if (NewState != State)
	{
		//Update the objective state member value, only if the new state is not the same as the current state
		State = NewState;
		//This will call method OnObjectiveStateChanged in ObjectiveWorldSubsystem
		StateChangedEvent.Broadcast(this, State);
	}
}

/*	At the start of the game, add this objective to the ObjectiveWorldSubsystem
	Each objective component belongs to 1 objective, there can be multiple	*/
void UObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->AddObjective(this);
	}
}

//Remove the objective when the game ends
void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->RemoveObjective(this);
	}

	Super::EndPlay(EndPlayReason);
}

