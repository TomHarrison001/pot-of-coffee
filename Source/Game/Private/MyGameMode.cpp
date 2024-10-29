#include "MyGameMode.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld(); // Returns the world the actor is in
	UGameInstance* gameInstance = World->GetGameInstance(); // Stores game instance
	FString error = "Players not fouwnd!";

	

	// Create local multiplayer mode
	ULocalPlayer* LocalPlayer = World->GetGameInstance()->CreateLocalPlayer(1, error, true);
}

//Return true if player can teleport
bool AMyGameMode::TeleportReady()
{
	return PadsActivated == 2;
}

//Return spawn pos for player0
FVector AMyGameMode::GetSpawnLevel()
{
	return LevelPositionsPlayer0[0];
}

void AMyGameMode::PadActivated()
{
	PadsActivated++;
}

void AMyGameMode::PadDeactivated()
{
	PadsActivated--;
}



