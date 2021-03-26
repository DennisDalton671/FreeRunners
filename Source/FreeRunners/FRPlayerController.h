// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FREERUNNERS_API AFRPlayerController : public APlayerController{
	GENERATED_BODY()
public:
	/** notify player about started match */
	//UFUNCTION(reliable, client)
	//void ClientGameStarted();

};
