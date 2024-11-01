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

//Return true if player can teleport
bool AMyGameMode::TeleportReady()
{
	return PadsActivated == 2;
}

// Return start position for level
FVector AMyGameMode::GetLevelStartPos(int player)
{
	int index = player + ActiveLevel * 2;
	return StartPositions[index];
}

void AMyGameMode::TeleportPlayers()
{
	AActor* Player = Players[0];
	Player->TeleportTo(GetLevelStartPos(0), Player->GetActorRotation());
	Player = Players[1];
	Player->TeleportTo(GetLevelStartPos(1), Player->GetActorRotation());
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
		ActiveLevel = FMath::RandRange(1, 9);
		GLog->Log(*FString::Printf(TEXT("ACTIVE LEVEL: %i"), ActiveLevel));
		TeleportPlayers();
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
	ActiveLevel = 0;
	TeleportPlayers();
}
