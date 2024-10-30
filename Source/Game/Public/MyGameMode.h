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

	bool TeleportReady();
	FVector GetSpawnLevel();


private:

	UPROPERTY(VisibleAnywhere, Category = "Pads")
	int PadsActivated;

	UPROPERTY(VisibleAnywhere, Category = "Levels")
	FVector LevelPositionsPlayer0[10] = { FVector(0.0f,-4150.0f,5.f) };
	FVector LevelPositionsPlayer1[10] = { FVector(0.0f,-4150.0f,5.f) };

	int Player0Score;
	int Player1Score;
	
};
