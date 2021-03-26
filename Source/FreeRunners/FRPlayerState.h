// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FRPlayerState.generated.h"

UCLASS()
class FREERUNNERS_API AFRPlayerState : public APlayerState{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated, BlueprintReadWrite, Category="FreeRunners")
	bool IsFinished;

	AFRPlayerState();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
};
