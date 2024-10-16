#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/PlayerInput.h"
#include "FixGameViewportClient.generated.h"

UCLASS()
class GAME_API UFixGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:
	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	virtual bool InputAxis(FViewport* InViewport, FInputDeviceId InputDevice, FKey Key, float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamepad = false) override;
	virtual void RemapControllerInput(FInputKeyEventArgs& InOutKeyEvent) override;

private:
	ULocalPlayer* GetLocalPlayerFromControllerId(int32 ControllerId) const;

	// A broadcast delegate broadcasting from UGameViewportClient::InputKey
	FOnInputKeySignature OnInputKeyEvent;

	// A broadcast delegate broadcasting from UGameViewportClient::InputAxis
	FOnInputAxisSignature OnInputAxisEvent;

	// Delegate for overriding input key behavior
	FOverrideInputKeyHandler OnOverrideInputKeyEvent;

	// Delegate for overriding input axis behavior
	FOverrideInputAxisHandler OnOverrideInputAxisEvent;

#if WITH_EDITOR
	// Delegate called when game viewport client received input key
	FOnGameViewportInputKey GameViewportInputKeyDelegate;
#endif
};
