// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameState.h"

#include "Net/UnrealNetwork.h"

AFRGameState::AFRGameState() {
	
}

void AFRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFRGameState, RoundTime);
	DOREPLIFETIME(AFRGameState, RoundPaused);
}