#include "Checkpoint.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Mesh
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CheckpointSceneComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMeshComponent"));
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap); //Set Mesh Collision to Overlap
	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACheckpoint::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// Check if OtherActor is valid and can be cast to AMainCharacter
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	if (MainChar != nullptr)
	{
		if (MainChar->GetTag() == "Player0")
		{
			AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->EndLevel(0);
		}
		if (MainChar->GetTag() == "Player1")
		{
			AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->EndLevel(1);
		}
	}
}
