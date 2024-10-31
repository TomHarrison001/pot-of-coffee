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
	void Player0Scored();
	void Player1Scored();
	void GetScore();

	void PadActivated();
	void PadDeactivated();

	AActor* Players[2];
	bool TeleportReady();
	FVector GetLevelStartPos(int player, int level);
	void TeleportPlayers(int level);

private:
	UPROPERTY(VisibleAnywhere, Category = "Pads")
	int PadsActivated;

	UPROPERTY(VisibleAnywhere, Category = "Levels")
	FVector StartPositions[20] = { FVector(0.0f, -5800.0f, 5.f), FVector(0.0f, -4400.0f, 5.f) };

	int Player0Score;
	int Player1Score;
	
};
