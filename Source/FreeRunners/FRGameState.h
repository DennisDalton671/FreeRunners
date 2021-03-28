// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FRGameState.generated.h"

UCLASS()
class FREERUNNERS_API AFRGameState : public AGameState{
	GENERATED_BODY()
public :
	UPROPERTY(Replicated, BlueprintReadWrite, Transient, Category="FreeRunners")
	float RoundTime;
	UPROPERTY(Replicated, BlueprintReadWrite, Transient, Category="FreeRunners")
	bool  RoundPaused;

	AFRGameState();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category="FreeRunners")
	FText GetTimeAsText();
};
