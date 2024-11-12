#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

UCLASS()
class GAME_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

public:
	void IncrementScore(int player);

	void PadActivated();
	void PadDeactivated();

	void StartTeleportTimer();
	void EndTeleportTimer();
	FTimerHandle LoopedTimerHandle;

	AActor* Players[2];
	bool TeleportReady();
	FVector GetLevelStartPos(int player); // returns player 1 or 2 start position for ActiveLevel
	void TeleportPlayers();

	void ResetLevel();
	void EndLevel(int winner);


private:
	UPROPERTY(VisibleAnywhere, Category = "Levels")
	int ActiveLevel;

	UPROPERTY(VisibleAnywhere, Category = "Levels")
	FVector StartPositions[20] = { FVector(-20.f, -180.f, 90.f), FVector(-20.f, 180.f, 90.f),  // player 1 spawn, player 2 spawn
		FVector(-400.f, 2600.f, 10.f), FVector(-400.f, 4000.f, 10.f),                          // player 1 level 1, player 2 level 1
		FVector(-500.f, 6400.f, 10.f), FVector(-500.f, 7800.f, 10.f),                          // player 1 level 2, player 2 level 2
		FVector(-500.f, 9200.f, 10.f), FVector(-500.f, 9400.f, 10.f),                          // player 1 level 3, player 2 level 3
		FVector(-570.f, 12300.f, 10.f), FVector(-500.f, 12500.f, 10.f),                        // player 1 level 4, player 2 level 4
		FVector(-570.f, 12300.f, 10.f), FVector(-500.f, 12500.f, 10.f),                        // spare - usued
		FVector(-570.f, 12300.f, 10.f), FVector(-500.f, 12500.f, 10.f),                        // spare - usued
		FVector(-570.f, 12300.f, 10.f), FVector(-500.f, 12500.f, 10.f),                        // spare - usued
		FVector(-570.f, 12300.f, 10.f), FVector(-500.f, 12500.f, 10.f),                        // spare - usued
		FVector(-570.f, 12300.f, 10.f), FVector(-500.f, 12500.f, 10.f),                        // spare - usued
	};

	// array containing index of played levels
	// TO-DO: empty array when player reaches 5 points
	UPROPERTY(VisibleAnywhere, Category = "Levels")
	TArray<int> PlayedLevels;

	UPROPERTY(VisibleAnywhere, Category = "Pads")
	int PadsActivated;

	// function returning if level is found in PlayedLevels array
	bool PlayedLevel();

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="HUD")
	int TimedLoopsRemaining;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="HUD")
	int P1Score;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="HUD")
	int P2Score;	

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "HUD")
	float timer;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "HUD")
	bool timerActive;
};
