

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameMode.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JumpPad.generated.h"

UCLASS()
class GAME_API AJumpPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Allows child components to move freely
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	USceneComponent* DefaultSceneRoot;

	// Collectable static mesh
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	UStaticMeshComponent* StaticMesh;

	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	//overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Jump Boost")
	float JumpHeight = 800;

};
