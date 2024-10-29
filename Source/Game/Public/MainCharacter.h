#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyGameMode.h"
#include "MainCharacter.generated.h"

UCLASS()
class GAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Mapping Context file
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	// Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	// Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	// Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	//Reference blueprint self
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor")
	AActor* self;

	// Called for jumping input
	void Jumping();

	//Return tag
	FString GetTag();

	// Called for looking input
	void Look(const FInputActionValue& Value);

	// Called for movement input
	void Move(const FInputActionValue& Value);

	void TeleportNewLocation();

	void StartTeleportTimer();
	void EndTeleportTimer();
	FTimerHandle LoopedTimerHandle;
	int32 TimedLoopsRemaining;
};