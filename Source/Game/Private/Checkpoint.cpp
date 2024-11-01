#include "Checkpoint.h"

// Sets default values for this component's properties
UCheckpoint::UCheckpoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCheckpoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UCheckpoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetAllValidActors(DeltaTime);
}

void UCheckpoint::GetAllValidActors(float DeltaTime)
{
	TArray<AActor*> OverlappingActors;

	if (TriggerVol != nullptr)
	{
		TriggerVol->GetOverlappingActors(OverlappingActors);

		for (AActor* Actor : OverlappingActors)
		{
			for (FName Tag : Actor->Tags)
			{
				if (Tag == "Player0")
				{
					AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
					GameMode->EndLevel(0);
				}
				if (Tag == "Player1")
				{
					AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
					GameMode->EndLevel(1);
				}
			}
		}
	}
}
