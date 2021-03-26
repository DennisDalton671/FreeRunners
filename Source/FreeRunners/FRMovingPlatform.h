// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRSyncObject.h"
#include "FRMovingPlatform.generated.h"

class UInterpToMovementComponent;

UCLASS()
class FREERUNNERS_API AFRMovingPlatform : public AFRSyncObject{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UInterpToMovementComponent* InterpComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	AFRMovingPlatform();
	AFRMovingPlatform(const FObjectInitializer& ObjectInitializer);

	void StartObject_Implementation() override;
};
