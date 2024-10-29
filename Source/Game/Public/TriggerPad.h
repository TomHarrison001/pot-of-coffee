

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameMode.h"
#include "MainCharacter.h"
#include "TriggerPad.generated.h"

UCLASS()
class GAME_API ATriggerPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Change the colour of the cube of the pad
	void ChangePadColour(FLinearColor NewColour);

	/** Collectable static mesh */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	UStaticMeshComponent* StaticMesh;

	/** Allows child components to move freely */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	USceneComponent* DefaultSceneRoot;

	//Active colour
	UPROPERTY(EditAnywhere, Category = "Pad")
	FLinearColor ActiveColour = FLinearColor::Green;

	//Other trigger pad
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	AActor* TriggerPad1;

	//Only activate when this tag touches it
	UPROPERTY(EditAnywhere, Category = "Default")
	FString ActivationTag;

	//Inactive colour
	UPROPERTY(EditAnywhere, Category = "Pad")
	FLinearColor InactiveColour = FLinearColor::Red;

	//on or off
	UPROPERTY(VisibleAnywhere, Category = "Pad")
	bool PadOn = false;

	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);



};
