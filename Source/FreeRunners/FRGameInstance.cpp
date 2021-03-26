// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameInstance.h"

#include "Blueprint/UserWidget.h"

UFRGameInstance::UFRGameInstance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer) {
	OnlineMode = EOnlineMode::Offline; //default to offline
	CurrentState = EFRState::Startup; //default to startup
}

bool UFRGameInstance::TransitionToState(EFRState state) {
	if(state == CurrentState) return false; //early out

	//remove old UI widgets
	switch(CurrentState) {
		case(EFRState::Startup):default: break;
		case(EFRState::Playing):     PlayUIWidget->RemoveFromParent(); break;
		case(EFRState::MainMenu):    MainMenuWidget->RemoveFromParent(); break;
		case(EFRState::Loading):     LoadingWidget->RemoveFromParent(); break;
		case(EFRState::LevelSelect): LevelSelectWidget->RemoveFromParent(); break;
		case(EFRState::Settings):    SettingsWidget->RemoveFromParent(); break;
	}

	//add new UI widgets
	switch(state) {
		case(EFRState::Startup):default: return false;
		case(EFRState::Playing):     PlayUIWidget->AddToViewport(); break;
		case(EFRState::MainMenu):    MainMenuWidget->AddToViewport(); break;
		case(EFRState::Loading):     LoadingWidget->AddToViewport(); break;
		case(EFRState::LevelSelect): LevelSelectWidget->AddToViewport(); break;
		case(EFRState::Settings):    SettingsWidget->AddToViewport(); break;
	}
	return true;
}