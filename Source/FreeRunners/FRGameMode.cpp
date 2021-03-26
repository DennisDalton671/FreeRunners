// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameMode.h"
#include "FRGameInstance.h"
#include "FRGameState.h"
#include "FRPlayerController.h"
#include "FRSyncObject.h"

AFRGameMode::AFRGameMode() : AGameMode() {
	bDelayedStart = true;

	PreRoundTime = 10;
	RespawnDelay = 3;
}

void AFRGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage){	
	Super::InitGame(MapName, Options, ErrorMessage);

	const UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance && Cast<UFRGameInstance>(GameInstance)->OnlineMode != EOnlineMode::Offline){
		bPauseable = false;
	}
}

void AFRGameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);
	PlayerControllers.Add(NewPlayer);
}

void AFRGameMode::HandleMatchIsWaitingToStart(){
	Super::HandleMatchIsWaitingToStart();

	if (bDelayedStart){
		// start warmup if needed
		AFRGameState* const MyGameState = Cast<AFRGameState>(GameState);
		if (MyGameState && MyGameState->RoundTime == 0){
			const bool bWantsMatchWarmup = !GetWorld()->IsPlayInEditor();
			if (bWantsMatchWarmup && PreRoundTime > 0){
				MyGameState->RoundTime = -PreRoundTime;
			}else{
				MyGameState->RoundTime = 0.0f;
			}
		}
	}
}

void AFRGameMode::HandleMatchHasStarted(){
	Super::HandleMatchHasStarted();

	AFRGameState* const MyGameState = Cast<AFRGameState>(GameState);
	MyGameState->RoundTime = 0;		

	// notify players
	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It){
		AFRPlayerController* PC = Cast<AFRPlayerController>(*It);
		if (PC){
			//PC->ClientGameStarted();
		}
	}
}

void AFRGameMode::Tick(float DeltaTime) {
	if(GetWorld()->IsPlayInEditor()) { return; }

	AFRGameState* const MyGameState = Cast<AFRGameState>(GameState);
	if(MyGameState && !MyGameState->RoundPaused) {
		MyGameState->RoundTime += DeltaTime;
	}
}

void AFRGameMode::MulticastStartSyncObjects_Implementation() {
	for(auto obj : SyncObjects) {
		obj->StartObject();
	}
}