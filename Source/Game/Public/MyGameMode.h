#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

USTRUCT(BlueprintType)
struct FLevelLocations
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Struct")
	FVector player0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Struct")
	FVector player1;
};

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
	FVector GetLevelStartPos(int player);
	void TeleportPlayers();

	void ResetLevel();
	void EndLevel(int winner);

private:
	UPROPERTY(VisibleAnywhere, Category = "Levels")
	int ActiveLevel;

	UPROPERTY(VisibleAnywhere, Category = "Levels")
	TArray<FLevelLocations> SpawnPositions =
	{
		{FVector(-400.0f,2600.0f,10.0f),FVector(-400.0f,4000.0f,10.0f)},
		{FVector(-500.0f,6400.0f,10.0f),FVector(-500.0f,7800.0f,10.0f)}
	};

	TArray<FLevelLocations>SpawnPositionsActive = SpawnPositions;

	UPROPERTY(VisibleAnywhere, Category = "Pads")
	int PadsActivated;

	void ShuffleArray(TArray<FLevelLocations>& array);


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
