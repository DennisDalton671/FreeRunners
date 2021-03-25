// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FreeRunnersGameModeBase.generated.h"

class AFRSyncObject;

UCLASS()
class FREERUNNERS_API AFreeRunnersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	TArray<AFRSyncObject*> SyncObjects;
};
