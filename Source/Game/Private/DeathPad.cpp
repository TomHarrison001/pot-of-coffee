


#include "DeathPad.h"

// Sets default values
ADeathPad::ADeathPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Mesh
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DeathPadSceneComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeathPadMeshComponent"));
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap); //Set Mesh Collision to Overlap
	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &ADeathPad::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ADeathPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathPad::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());

	if (MainChar != nullptr)
	{
		MainChar-> TeleportTo(GameMode->GetLevelStartPos((MainChar->GetTag() == "Player0") ? 0 : 1), GetActorRotation());
	}
}
