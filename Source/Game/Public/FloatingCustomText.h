

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "FloatingCustomText.generated.h"

UCLASS()
class GAME_API AFloatingCustomText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingCustomText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UTextRenderComponent* MyText; 

	UPROPERTY(EditAnywhere, category = "Text to display")
	FString InputText;

};
