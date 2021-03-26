// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameInstance.h"

UFRGameInstance::UFRGameInstance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer) {
	OnlineMode = EOnlineMode::Offline; //default to offline
	CurrentState = EFRState::Startup; //default to startup
}

bool UFRGameInstance::IsCurrentState(EFRState state) {
	return state == CurrentState;
}

bool UFRGameInstance::TransitionToState(EFRState state) {
	if(state == CurrentState) return false;

	switch(state) {
		case(EFRState::MainMenu):default: {}
		case(EFRState::Startup): {}
		
	}
	return true;
}