// Fill out your copyright notice in the Description page of Project Settings.


#include "FRInfiniteBall.h"

AFRInfiniteBall::AFRInfiniteBall(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	BallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMeshComponent"));
	BallMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	BallMeshComponent->SetStaticMesh(SphereMesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterial>BasicMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	BallMeshComponent->SetMaterial(0, BasicMat.Object);
}

void AFRInfiniteBall::BeginPlay(){
	Super::BeginPlay();
	
	_timer = delay;
}

void AFRInfiniteBall::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(ServerStart) {
		_timer -= DeltaTime;
		if(_timer < 0) {
			Destroy();
		}
	}
}

void AFRInfiniteBall::StartObject() {
	Super::StartObject();

	BallMeshComponent->SetSimulatePhysics(true);
}

void AFRInfiniteBall::Destroyed() {
	if(GetWorld()->IsGameWorld()) {
		FVector temp = GetRootComponent()->GetRelativeLocation();
		GetWorld()->SpawnActor(AFRInfiniteBall::StaticClass(), &temp, 0);
	}
}