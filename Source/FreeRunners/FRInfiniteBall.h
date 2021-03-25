// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRSyncObject.h"
#include "FRInfiniteBall.generated.h"

/**
 * 
 */
UCLASS()
class FREERUNNERS_API AFRInfiniteBall : public AFRSyncObject
{
	GENERATED_BODY()

	float _timer;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BallMeshComponent;

	UPROPERTY(BlueprintReadWrite)
	float delay = 5.f;

	AFRInfiniteBall(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	virtual void StartObject() override;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
};
