


#include "RoundEndPad.h"

// Sets default values
ARoundEndPad::ARoundEndPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}






//STILL NEED TO FINISH & COMPLETE







// Called when the game starts or when spawned
void ARoundEndPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoundEndPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoundEndPad::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// Check if OtherActor is valid and can be cast to AMainCharacter
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	if (MainChar != nullptr)
	{
		if (MainChar->GetTag() == "Player0")
		{
			AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->EndLevel(0);
		}
		if (MainChar->GetTag() == "Player1")
		{
			AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->EndLevel(1);
		}
	}
}

