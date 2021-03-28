// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameMode.h"
#include "FRGameInstance.h"
#include "FRGameState.h"
#include "FRPlayerController.h"
#include "FRSyncObject.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"

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
	MyGameState->RoundPaused = false;

	// notify players
	/*
	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It){
		AFRPlayerController* PC = Cast<AFRPlayerController>(*It);
		if (PC){
			//PC->ClientGameStarted();
		}
	}
	*/

	//spawn players
	//SpawnPlayerActors();

	//start sync objects
	MulticastStartSyncObjects();
}

void AFRGameMode::Tick(float DeltaTime) {
	if(!GetWorld()->IsGameWorld()) { return; }

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

void AFRGameMode::SpawnPlayerActors() {
	for(APlayerController* pc : PlayerControllers) {
		APlayerStart* start = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
		ConstructorHelpers::FClassFinder<ACharacter> FRCharacter(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
		FActorSpawnParameters params; params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		APawn* pawn = Cast<APawn>(GetWorld()->SpawnActor(FRCharacter.Class, &start->GetTransform(), params));
		pc->Possess(pawn);
	}
}