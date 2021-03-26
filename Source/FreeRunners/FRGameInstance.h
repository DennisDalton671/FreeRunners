// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FRGameInstance.generated.h"

UENUM()
enum class EFRState : uint8{
	Startup,
	Playing,
	MainMenu,
	Loading,
	Multiplayer,
	LevelSelect,
	Settings
};

UENUM()
enum class EOnlineMode : uint8{
	Offline,
	LAN,
	Online
};



UCLASS()
class FREERUNNERS_API UFRGameInstance : public UGameInstance{
	GENERATED_BODY()

public:


	/** Current online mode of the game (offline, LAN, or online) */
	EOnlineMode OnlineMode;
	/** Current state of the game or menu */
	EFRState CurrentState;

	UFRGameInstance(const FObjectInitializer& ObjectInitializer);

	/** Sends the game to the specified state and updates the UI */
	//Returns true if the state changed
	bool TransitionToState(EFRState NewState);
	/** checks if the state equals the provided one */
	bool IsCurrentState(EFRState state);
};
