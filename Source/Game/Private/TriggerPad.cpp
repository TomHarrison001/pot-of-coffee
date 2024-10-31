#include "TriggerPad.h"

// Sets default values
ATriggerPad::ATriggerPad()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Mesh
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TriggerPadSceneComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerPadMeshComponent"));

	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap); //Set Mesh Collision to Overlap

	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &ATriggerPad::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATriggerPad::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ATriggerPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATriggerPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerPad::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// Check if OtherActor is valid and can be cast to AMainCharacter
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	if (MainChar)
	{
		//Only activate the pad if tags match
		if (ActivationTag == MainChar->GetTag())
		{
			// Log the tag with additional checks for empty tags handled in GetTag()
			GLog->Log(MainChar->GetTag() + " Stepped on the pad");
			ChangePadColour(ActiveColour);

			//Set pad to on
			//Check if can teleport, and if can, teleport
			PadOn = true;
			AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->PadActivated();
			GameMode->Players[(ActivationTag == "Player0") ? 0 : 1] = MainChar;
			if (GameMode->TeleportReady())
			{
				MainChar->StartTeleportTimer();
			}
		}
		else
		{
			GLog->Log("Wrong Pad.");
		}
	}
}

void ATriggerPad::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	//When stepped off, change back to red
	ChangePadColour(InactiveColour);
	PadOn = false;
	AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->PadDeactivated();
}

//Change pad colour
void ATriggerPad::ChangePadColour(FLinearColor NewColour)
{
	//If trigger volume is not null
	if (StaticMesh != nullptr)
	{
		//Find the cube relating to the trigger volume
		//WARNING - Will break if any other StaticMeshes are added to trigger vol
		UStaticMeshComponent* Cube = StaticMesh;

		if (Cube != nullptr)
		{
			//Create a new material (dynamic material) that can be changed during gameplay
			UMaterialInstanceDynamic* CubeMaterial = Cube->CreateAndSetMaterialInstanceDynamic(0);

			if (CubeMaterial != nullptr)
			{
				//Change pad colour
				CubeMaterial->SetVectorParameterValue(FName("Color"), NewColour);
				GLog->Log("Change pad colour to " + FString(NewColour.ToString()));
			}
		}
	}
}
