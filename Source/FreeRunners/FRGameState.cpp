// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameState.h"

#include "Net/UnrealNetwork.h"

AFRGameState::AFRGameState() {
	RoundTime = 0;
	RoundPaused = false;
}

void AFRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFRGameState, RoundTime);
	DOREPLIFETIME(AFRGameState, RoundPaused);
}

FText AFRGameState::GetTimeAsText() {
	FNumberFormattingOptions options{};
	options.MinimumFractionalDigits = 3; options.MaximumFractionalDigits = 3;
	options.MinimumIntegralDigits = 1;   options.MaximumIntegralDigits = 100;
	return FText::AsNumber(RoundTime, &options);
}