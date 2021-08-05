#include "FPCubePushComponent.h"

// Sets default values for this component's properties
UFPCubePushComponent::UFPCubePushComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UFPCubePushComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Delegate is already setup, bound to OnObjectiveStateChanged() when OnStateChanged (in objective component) is broadcast.
	//Broadcast ObjectiveComponent->OnStateChanged once the player jumps on top of the cube


}

