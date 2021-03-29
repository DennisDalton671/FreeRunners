// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FRGameState.generated.h"

UCLASS()
class FREERUNNERS_API AFRGameState : public AGameState{
	GENERATED_BODY()
public :
	UPROPERTY(Replicated, BlueprintReadWrite, Category="FreeRunners")
	float RoundTime;
	UPROPERTY(Replicated, BlueprintReadWrite, Category="FreeRunners")
	bool  RoundPaused;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "FreeRunners")
	int32 PlayerCount;

	AFRGameState();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category="FreeRunners")
	FText GetTimeAsText();
};
