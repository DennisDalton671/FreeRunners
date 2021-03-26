// Fill out your copyright notice in the Description page of Project Settings.


#include "FRInfiniteBall.h"

AFRInfiniteBall::AFRInfiniteBall() : AFRSyncObject() {
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(true);

	BallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMeshComponent"));
	BallMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	BallMeshComponent->SetStaticMesh(SphereMesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterial>BasicMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	BallMeshComponent->SetMaterial(0, BasicMat.Object);
}

AFRInfiniteBall::AFRInfiniteBall(const FObjectInitializer& ObjectInitializer) : AFRSyncObject(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(true);

	BallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMeshComponent"));
	BallMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	BallMeshComponent->SetStaticMesh(SphereMesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterial>BasicMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	BallMeshComponent->SetMaterial(0, BasicMat.Object);
}

void AFRInfiniteBall::BeginPlay(){
	Super::BeginPlay();
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFRInfiniteBall::Respawn, delay);
}

void AFRInfiniteBall::Respawn() {
	if(GetWorld()->IsGameWorld()) {
		FVector loc = GetRootComponent()->GetRelativeLocation();
		AFRInfiniteBall* newBall = Cast<AFRInfiniteBall, AActor>(GetWorld()->SpawnActor(AFRInfiniteBall::StaticClass(), &loc, 0));
		if(newBall) {
			newBall->ServerStart = true;
			newBall->BallMeshComponent->SetSimulatePhysics(true);
		}
	}
	Destroy();
}

void AFRInfiniteBall::StartObject_Implementation() {
	AFRSyncObject::StartObject_Implementation();

	BallMeshComponent->SetSimulatePhysics(true);
}