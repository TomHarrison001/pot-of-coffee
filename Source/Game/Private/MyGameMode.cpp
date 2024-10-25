#include "MyGameMode.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld(); // Returns the world the actor is in
	UGameInstance* gameInstance = World->GetGameInstance(); // Stores game instance
	FString error = "Players not found!";

	

	// Create local multiplayer mode
	ULocalPlayer* LocalPlayer = World->GetGameInstance()->CreateLocalPlayer(1, error, true);
}

