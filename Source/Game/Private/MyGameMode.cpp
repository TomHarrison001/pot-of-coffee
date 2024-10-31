#include "MyGameMode.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld(); // Returns the world the actor is in
	UGameInstance* gameInstance = World->GetGameInstance(); // Stores game instance
	FString error = "Players not found!";

	// Create local multiplayer mode
	ULocalPlayer* LocalPlayer = World->GetGameInstance()->CreateLocalPlayer(1, error, true);

	TimedLoopsRemaining = 3;
	timerActive = false;
}

void AMyGameMode::IncrementScore(int player)
{
	if (player == 0)
	{
		P1Score++;
	}
	else
	{
		P2Score++;
	}
}

void AMyGameMode::GetScore()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("P1 score: %i"), P1Score));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("P2 score: %i"), P2Score));
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
	return StartPositions[player + level * 2];
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
	
	if (TeleportReady())
	{
		StartTeleportTimer();
	}
}

void AMyGameMode::PadDeactivated()
{
	PadsActivated--;
}

//Start teleport countdown
void AMyGameMode::StartTeleportTimer()
{
	//Set timer to 3 seconds, and start the timer (5 mins)
	GLog->Log("Game Starting!");
	GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
	GetWorldTimerManager().SetTimer(LoopedTimerHandle, this, &AMyGameMode::EndTeleportTimer, 1.0f, true, 1.0f);
}

//Timer finished, teleport
void AMyGameMode::EndTeleportTimer()
{
	//Log seconds till teleport repeatidly
	GLog->Log(FString::FromInt(TimedLoopsRemaining));

	//If not all pads are active during teleport sequence, interupt and cancel teleport
	if (!TeleportReady())
	{
		GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
		GLog->Log("Teleport Aborted... Remain on pads to telport.");
		TimedLoopsRemaining = 3;
	}
	else if (--TimedLoopsRemaining < 0)
	{
		//Teleport the main char
		GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
		TimedLoopsRemaining = 3;
		GLog->Log("Teleporting...");

		GetScore();
		TeleportPlayers(0);
		ResetLevel();
	}
}

// teleports to level and resets timer
void AMyGameMode::ResetLevel()
{
	timer = 0;
	timerActive = true;
}

// determines winner and returns players to lobby
void AMyGameMode::EndLevel(int winner)
{
	timerActive = false;
	IncrementScore(winner);
	TeleportPlayers(1);
}
