


#include "TriggerPadComponent.h"

// Sets default values for this component's properties
UTriggerPadComponent::UTriggerPadComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTriggerPadComponent::BeginPlay()
{
	Super::BeginPlay();

	//Force pad to be red at the start
	ChangePadColour(InactiveColour);
	
}


// Called every frame
void UTriggerPadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get actors in trigger zone every frame
	GetAllValidActors(DeltaTime);
}

void UTriggerPadComponent::ChangePadColour(FLinearColor NewColour)
{
		//If trigger volume is not null
		if (TriggerVol != nullptr)
		{
			//Find the cube relating to the trigger volume
			//WARNING - Will break if any other StaticMeshes are added to trigger vol
			UStaticMeshComponent* Cube = TriggerVol->FindComponentByClass<UStaticMeshComponent>();

			if (Cube != nullptr)
			{
				//Create a new material (dynamic material) that can be changed during gameplay
				UMaterialInstanceDynamic* CubeMaterial = Cube->CreateAndSetMaterialInstanceDynamic(0);

				if (CubeMaterial != nullptr)
				{
					//Log pad is active and change the colour
					GLog->Log("Pad Active.");
					CubeMaterial->SetVectorParameterValue(FName("Color"), NewColour);
				}
			}
		}
}

void UTriggerPadComponent::GetAllValidActors(float DeltaTime)
{
	TArray<AActor*> OverlappingActors; // List of Actors to be stored here

	if (TriggerVol != nullptr) // Check if TriggerVolume has been assigned
	{
		// Gets details of each Actor that is in TriggerVolume and stores it array.
		TriggerVol->GetOverlappingActors(OverlappingActors);

		for (AActor* Actor : OverlappingActors)
		{
			for (FName Tag : Actor->Tags) // Gets list of all tags from Actor
			{
				GLog->Log(Tag.ToString()); // Output to console

				if (Tag == PlayerTag) // Open door when Actor has “Player” tag
				{
					ChangePadColour(ActiveColour);
				}
			}
		}
		if (OverlappingActors.IsEmpty())
		{
			//If there are no actors in it, make the pad red
			ChangePadColour(InactiveColour);
		}
	}
}


