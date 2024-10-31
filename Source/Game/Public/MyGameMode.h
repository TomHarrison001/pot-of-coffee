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
	void GetScore();

	void PadActivated();
	void PadDeactivated();

	void StartTeleportTimer();
	void EndTeleportTimer();
	FTimerHandle LoopedTimerHandle;

	AActor* Players[2];
	bool TeleportReady();
	FVector GetLevelStartPos(int player, int level);
	void TeleportPlayers(int level);

	void ResetLevel();
	void EndLevel(int winner);

private:
	UPROPERTY(VisibleAnywhere, Category = "Pads")
	int PadsActivated;

	UPROPERTY(VisibleAnywhere, Category = "Levels")
	FVector StartPositions[20] = { FVector(0.f, -5800.f, 5.f), FVector(0.f, -4400.f, 5.f),
		FVector(-20.f, -180.f, 90.f), FVector(-20.f, 180.f, 90.f) };

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
