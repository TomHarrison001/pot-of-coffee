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

void AMyGameMode::Player0Scored()
{
	Player0Score++;
}

void AMyGameMode::Player1Scored()
{
	Player1Score++;
}

void AMyGameMode::GetScore()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Player 2 score: %i"), Player1Score));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Player 1 score: %i"), Player0Score));
	}
}

//Return true if player can teleport
bool AMyGameMode::TeleportReady()
{
	return PadsActivated == 2;
}

// Return start position for level
FVector AMyGameMode::GetLevelStartPos(int player, int level)
{
	return StartPositions[level * 2 + player];
}

void AMyGameMode::TeleportPlayers(int level)
{
	AActor* Player = Players[0];
	Player->TeleportTo(GetLevelStartPos(0, level), Player->GetActorRotation());
	Player = Players[1];
	Player->TeleportTo(GetLevelStartPos(1, level), Player->GetActorRotation());
}

void AMyGameMode::PadActivated()
{
	PadsActivated++;
}

void AMyGameMode::PadDeactivated()
{
	PadsActivated--;
}
