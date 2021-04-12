// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameInstance.h"

#include "Blueprint/UserWidget.h"

UFRGameInstance::UFRGameInstance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer) {
	OnlineMode = EOnlineMode::Offline; //default to offline
	CurrentState = EFRState::None; //default to none
}

UUserWidget* UFRGameInstance::TransitionToState(EFRState state) {
	if(state == CurrentState) return nullptr; //early out

	//remove old UI widgets
	FString oldState;
	switch(CurrentState) {
		case(EFRState::None):default:                                       oldState = FString("NONE");     break;
		case(EFRState::Playing):     PlayUIWidget->RemoveFromParent();      oldState = FString("PLAYING");     break;
		case(EFRState::MainMenu):    MainMenuWidget->RemoveFromParent();    oldState = FString("MAINMENU");    break;
		case(EFRState::Loading):     LoadingWidget->RemoveFromParent();     oldState = FString("LOADING");     break;
		case(EFRState::Multiplayer): MultiplayerWidget->RemoveFromParent(); oldState = FString("MULTIPLAYER"); break;
		case(EFRState::LevelSelect): LevelSelectWidget->RemoveFromParent(); oldState = FString("LEVELSELECT"); break;
		case(EFRState::Settings):    SettingsWidget->RemoveFromParent();    oldState = FString("SETTINGS");    break;
	}
	CurrentState = state;

	//add new UI widgets
	FString newState;
	UUserWidget* out = nullptr;
	switch(state) {
		default:                                                         newState = FString("NONE");        out = nullptr;           break;
		case(EFRState::Playing):     PlayUIWidget->AddToViewport();      newState = FString("PLAYING");     out = PlayUIWidget;      break;
		case(EFRState::MainMenu):    MainMenuWidget->AddToViewport();    newState = FString("MAINMENU");    out = MainMenuWidget;    break;
		case(EFRState::Loading):     LoadingWidget->AddToViewport();     newState = FString("LOADING");     out = LoadingWidget;     break;
		case(EFRState::Multiplayer): MultiplayerWidget->AddToViewport(); newState = FString("MULTIPLAYER"); out = MultiplayerWidget; break;
		case(EFRState::LevelSelect): LevelSelectWidget->AddToViewport(); newState = FString("LEVELSELECT"); out = LevelSelectWidget; break;
		case(EFRState::Settings):    SettingsWidget->AddToViewport();    newState = FString("SETTINGS");    out = SettingsWidget;    break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Switching state from %s to %s"), *oldState, *newState);
	return out;
}