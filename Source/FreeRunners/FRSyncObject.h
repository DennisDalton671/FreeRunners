// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRSyncObject.generated.h"

UCLASS()
class FREERUNNERS_API AFRSyncObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFRSyncObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	int SyncObjectIndex{};

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
