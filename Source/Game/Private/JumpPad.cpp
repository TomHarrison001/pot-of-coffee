#include "JumpPad.h"

// Sets default values
AJumpPad::AJumpPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Mesh
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("JumpPadSceneComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JumpPadMeshComponent"));
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap); //Set Mesh Collision to Overlap
	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AJumpPad::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AJumpPad::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AJumpPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AJumpPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJumpPad::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	//Cast to main char
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	//Set actors jump height to new value
	MainChar->GetCharacterMovement()->JumpZVelocity = JumpHeight;
	//Force player to be in walking state (allows to jump if not floored)
	MainChar->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	//Jump!
	MainChar->Jump();
}

void AJumpPad::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	//Cast to main char
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	//Return actor back to normal jump height
	MainChar->GetCharacterMovement()->JumpZVelocity = MainChar->NormJumpHeight;
}
