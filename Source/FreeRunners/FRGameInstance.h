// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FRGameInstance.generated.h"

UENUM(BlueprintType)
enum class EFRState : uint8{ None, Playing, MainMenu, Loading, Multiplayer, LevelSelect, Settings };

UENUM(BlueprintType)
enum class EOnlineMode : uint8{ Offline, LAN, Online };

class UUserWidget;

UCLASS()
class FREERUNNERS_API UFRGameInstance : public UGameInstance{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	UUserWidget* PlayUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	UUserWidget* MainMenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	UUserWidget* LoadingWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	UUserWidget* MultiplayerWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	UUserWidget* LevelSelectWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	UUserWidget* SettingsWidget;

	/** Current online mode of the game (offline, LAN, or online) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	EOnlineMode OnlineMode;
	/** Current state of the game or menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	EFRState CurrentState;

	UFRGameInstance(const FObjectInitializer& ObjectInitializer);

	/** Sends the game to the specified state and updates the UI  */
	UFUNCTION(BlueprintCallable, Category="FreeRunners")
	UUserWidget* TransitionToState(EFRState NewState);
};
