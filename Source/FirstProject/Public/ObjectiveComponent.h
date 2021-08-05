#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveComponent.generated.h"

//Store the possible objective states
UENUM()
enum class EObjectiveState
{
	OS_Inactive = 0		UMETA(DisplayName = "Inactive"),
	OS_Active = 1		UMETA(DisplayName = "Active"),
	OS_Completed = 2	UMETA(DisplayName = "Completed"),
};

//Each objective is an instance of ObjectiveComponent
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPROJECT_API UObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Sets default values for this component's properties
	UObjectiveComponent();

	//Return the name/description of the objective set in the editor. This allows us to identify each objective in the array
	UFUNCTION(BlueprintCallable)
	const FString& GetDescription() const { return Description; }

	/*	Declare new event delegate for a StateChanged event.
		The delegate is declared here, and bound in the WorldSubsystem in AddObjective	*/
	DECLARE_EVENT_TwoParams(FObjectiveComponent, FStateChanged, UObjectiveComponent*, EObjectiveState)	
	
	//Declare method that returns the StateChangedEvent object (instance of FStateChanged)
	FStateChanged& OnStateChanged() { return StateChangedEvent; }

	UFUNCTION(BlueprintCallable)
	EObjectiveState GetState() const { return State; }

	void SetState(EObjectiveState NewState);

protected:
	//Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	EObjectiveState State;
	
	//Object/individual event instance of FStateChanged		
	FStateChanged StateChangedEvent;			
};
