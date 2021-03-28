// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameInstance.h"

#include "Blueprint/UserWidget.h"

UFRGameInstance::UFRGameInstance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer) {
	OnlineMode = EOnlineMode::Offline; //default to offline
	CurrentState = EFRState::Startup; //default to startup
}

bool UFRGameInstance::TransitionToState(EFRState state) {
	if(state == CurrentState || state == EFRState::Startup) return false; //early out

	//remove old UI widgets
	FString oldState;
	switch(CurrentState) {
		case(EFRState::Startup):default:                                    oldState = FString("STARTUP");     break;
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
	switch(state) {
		case(EFRState::Playing):     PlayUIWidget->AddToViewport();      newState = FString("PLAYING");     break;
		case(EFRState::MainMenu):    MainMenuWidget->AddToViewport();    newState = FString("MAINMENU");    break;
		case(EFRState::Loading):     LoadingWidget->AddToViewport();     newState = FString("LOADING");     break;
		case(EFRState::Multiplayer): MultiplayerWidget->AddToViewport(); newState = FString("MULTIPLAYER"); break;
		case(EFRState::LevelSelect): LevelSelectWidget->AddToViewport(); newState = FString("LEVELSELECT"); break;
		case(EFRState::Settings):    SettingsWidget->AddToViewport();    newState = FString("SETTINGS");    break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Switching state from %s to %s"), *oldState, *newState);
	return true;
}