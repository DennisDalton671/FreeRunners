// Fill out your copyright notice in the Description page of Project Settings.
#include "FRPlayerState.h"

#include "Net/UnrealNetwork.h"

AFRPlayerState::AFRPlayerState() {
	IsFinished = false;
}

void AFRPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFRPlayerState, IsFinished);
}