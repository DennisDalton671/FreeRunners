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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners", Meta = (MakeEditWidget = true))
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners", Meta = (MakeEditWidget = true))
	FVector EndLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FreeRunners")
	float Duration;

	AFRMovingPlatform();
	AFRMovingPlatform(const FObjectInitializer& ObjectInitializer);

	void BeginPlay() override;

	void StartObject_Implementation() override;
};
