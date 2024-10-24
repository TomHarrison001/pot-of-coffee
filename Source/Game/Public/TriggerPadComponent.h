

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "TriggerPadComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UTriggerPadComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerPadComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	//Change the colour of the cube of the pad
	void ChangePadColour(FLinearColor NewColour);

	//Get all actors within trigger zone
	void GetAllValidActors(float DeltaTime);

private:
	//Active colour
	UPROPERTY(EditAnywhere, Category = "Pad")
	FLinearColor ActiveColour = FLinearColor::Green;

	//Inactive colour
	UPROPERTY(EditAnywhere, Category = "Pad")
	FLinearColor InactiveColour = FLinearColor::Red;

	//Only can be activated by actors with this tag
	UPROPERTY(EditAnywhere, Category = "Pad")
	FString PlayerTag;

	//Reference to the trigger volume
	UPROPERTY(EditAnywhere, Category = "Pad")
	ATriggerVolume* TriggerVol;

	//on or off
	UPROPERTY(VisibleAnywhere, Category = "Pad")
	bool PadOn = false;

};
