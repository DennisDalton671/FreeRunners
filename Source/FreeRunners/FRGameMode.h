// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FRGameMode.generated.h"

class AFRSyncObject;
class APlayerController;

UCLASS()
class FREERUNNERS_API AFRGameMode : public AGameMode{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FreeRunners")
	int32 PreRoundTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FreeRunners")
	int32 RespawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FreeRunners")
	TArray<AFRSyncObject*> SyncObjects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FreeRunners")
	TArray<APlayerController*> PlayerControllers;

	/** Initialize the game. This is called before actors' PreInitializeComponents. */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	/** called before startmatch */
	virtual void HandleMatchIsWaitingToStart() override;
	/** starts new match */
	virtual void HandleMatchHasStarted() override;
	/** updates the game state's round time */
	virtual void Tick(float DeltaTime) override;
	
	AFRGameMode();

	/** [server + local] starts all sync objects */
	UFUNCTION(NetMulticast, Reliable, Category="FreeRunners")
	void MulticastStartSyncObjects();
	void MulticastStartSyncObjects_Implementation();

	/** [server] spawns actors for all players */
	void SpawnPlayerActors();
};
