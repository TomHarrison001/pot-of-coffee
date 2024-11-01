#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MyGameMode.h"
#include "Checkpoint.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCheckpoint : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCheckpoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void GetAllValidActors(float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	ATriggerVolume* TriggerVol;

};
