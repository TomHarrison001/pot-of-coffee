#include "GunCollectable.h"

// Sets default values
AGunCollectable::AGunCollectable()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Mesh
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GunCollectableSceneComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunCollectableMeshComponent"));

	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap); //Set Mesh Collision to Overlap

	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AGunCollectable::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AGunCollectable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunCollectable::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), *OtherActor->GetName());

	if (Cast<AMainCharacter>(OtherActor))
	{
		AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);

		MainChar->CollectGun(); //Set main character to 'gun mode'
	}
}

