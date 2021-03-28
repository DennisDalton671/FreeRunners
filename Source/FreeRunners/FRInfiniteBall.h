// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRSyncObject.h"
#include "FRInfiniteBall.generated.h"

UCLASS()
class FREERUNNERS_API AFRInfiniteBall : public AFRSyncObject{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BallMeshComponent;

	UPROPERTY(BlueprintReadWrite)
	float delay = 5.f;

	FTimerHandle TimeHandle;

	AFRInfiniteBall();
	AFRInfiniteBall(const FObjectInitializer& ObjectInitializer);

	void StartObject_Implementation() override;
	void Respawn();
};
