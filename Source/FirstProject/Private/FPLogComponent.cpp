#include "FPLogComponent.h"
#include "Engine/TriggerBox.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UFPLogComponent::UFPLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Error, TEXT("FP Component Created"));
}

// Called when the game starts
void UFPLogComponent::BeginPlay()
{
	Super::BeginPlay();

	CubeState = ECubeState::CS_Waiting;

	//On object construction, output DataString which is set in the editor
	UE_LOG(LogTemp, Warning, TEXT("UFPLogComponent::BeginPlay() %s"), *DataString);		
}

// Called every frame
void UFPLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Delegate is already setup, bound to OnObjectiveStateChanged() when OnStateChanged (in objective component) is broadcast.
	//Broadcast ObjectiveComponent->OnStateChanged once the player jumps on top of the cube

	//Only check for the JumpedOn event if the state is still waiting
	if (CubeState == ECubeState::CS_Waiting)
	{
		//Get the player pawn to check for the overlap. Additional checks to prevent crashes		
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

		//If player is overlapping the checkbox
		if (PlayerPawn && CheckBox->IsOverlappingActor(PlayerPawn))
		{			
			OnJumpedOn();
		}
	}
}

void UFPLogComponent::OnJumpedOn()
{
	//Update cube state
	//Set objective state
	CubeState = ECubeState::CS_JumpedOn;

	//Find the objective component, then call the setstate method passing in the new required objective state
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
}

