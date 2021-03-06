// Fill out your copyright notice in the Description page of Project Settings.


#include "FRMovingPlatform.h"
#include "Components/InterpToMovementComponent.h"

AFRMovingPlatform::AFRMovingPlatform() : AFRSyncObject() {
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	InterpComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterpToMovement"));
	InterpComponent->BehaviourType = EInterpToBehaviourType::PingPong;
	InterpComponent->bAutoActivate = false;
}

AFRMovingPlatform::AFRMovingPlatform(const FObjectInitializer& ObjectInitializer) : AFRSyncObject(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMeshComponent"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	InterpComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterpToMovement"));
	InterpComponent->BehaviourType = EInterpToBehaviourType::PingPong;
	InterpComponent->bAutoActivate = false;
}

void AFRMovingPlatform::BeginPlay(){
	Super::BeginPlay();
	
	InterpComponent->ControlPoints = TArray<FInterpControlPoint>({FInterpControlPoint(StartLocation, true), FInterpControlPoint(EndLocation, true)});
	InterpComponent->Duration = Duration;
	InterpComponent->FinaliseControlPoints();
}

void AFRMovingPlatform::StartObject_Implementation() {
	AFRSyncObject::StartObject_Implementation();

	InterpComponent->Activate();
}