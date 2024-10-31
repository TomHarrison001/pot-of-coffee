#include "MainCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jumping);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
	}
}

void AMainCharacter::Jumping()
{
	Jump();
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Calculate forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

//Returns the first tag, returns no tags if there are no tags in first slot
FString AMainCharacter::GetTag()
{
	if (Tags.Num() > 0)
	{
		return Tags[0].ToString();
	}
	return FString("No Tags");
}

//Start teleport countdown
void AMainCharacter::StartTeleportTimer()
{
	//Set timer to 5 seconds, and start the timer (5 mins)
	GLog->Log("Game Starting!");
	GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
	TimedLoopsRemaining = 5;
	GetWorldTimerManager().SetTimer(LoopedTimerHandle, this, &AMainCharacter::EndTeleportTimer, 1.0f, true, 1.0f);
}

//Timer finished, teleport
void AMainCharacter::EndTeleportTimer()
{
	AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());

	//Log seconds till teleport repeatidly
	GLog->Log(FString::FromInt(TimedLoopsRemaining));
	
	//If not all pads are active during teleport sequence, interupt and cancel teleport
	if (!GameMode->TeleportReady())
	{
		GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
		GLog->Log("Teleport Aborted... Remain on pads to telport.");
	}
	else if (--TimedLoopsRemaining < 0)
	{
		//Teleport the main char
		GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
		GLog->Log("Teleporting...");

		GameMode->GetScore();
		GameMode->TeleportPlayers(0);
	}	
}
