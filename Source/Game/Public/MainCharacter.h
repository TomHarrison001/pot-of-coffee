#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyGameMode.h"
#include "Gun.h"
#include "Projectile.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.generated.h"

class AGun;

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
	
	// FPS camera
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* FPSCameraComponent;

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

	// Shoot Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ShootAction;

	// Gun muzzle offset from the camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	// Called for Shoot input
	void Shoot();

	// Reference blueprint self
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor")
	AActor* self;

	// Called for jumping input
	void Jumping();

	//Return tag
	FString GetTag();

	// Overlap begin function - projectile
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// Called for looking input
	void Look(const FInputActionValue& Value);

	// Called for movement input
	void Move(const FInputActionValue& Value);

	// Gun Class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	// Gun Collected Bool (used for animations)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	bool GunCollected;

	// Gun Collected Function
	void CollectGun();

	// Gun Dropped Function
	void DropGun();

	//Normal Jump Height 
	float NormJumpHeight;
};
