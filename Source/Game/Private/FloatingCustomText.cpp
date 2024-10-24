


#include "FloatingCustomText.h"

// Sets default values
AFloatingCustomText::AFloatingCustomText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("My 	Text Component")); //Initialises UTextRenderComponent
	MyText->SetWorldSize(150.f); // Set size of text
	MyText->SetText(FText::FromString(TEXT("defaultText")));// Set Text

	RootComponent = MyText; // adding MyText to root component. Without doing this you wont see the component being displayed.

}

// Called when the game starts or when spawned
void AFloatingCustomText::BeginPlay()
{
	Super::BeginPlay();

	if (!InputText.IsEmpty())
	{
		MyText->SetText(FText::FromString(InputText));
	}

}

// Called every frame
void AFloatingCustomText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

