#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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

	//Custom tag that applies in BeginPlay()
	//WARNING - Currently only applies to Controller character - on purpose.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FString tag;

	//Reference blueprint self
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor")
	AActor* self;

	// Called for jumping input
	void Jumping();

	// Called for looking input
	void Look(const FInputActionValue& Value);

	// Called for movement input
	void Move(const FInputActionValue& Value);
};
