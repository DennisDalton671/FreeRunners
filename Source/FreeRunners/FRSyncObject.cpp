// Fill out your copyright notice in the Description page of Project Settings.
#include "FRSyncObject.h"
#include "FreeRunnersGameModeBase.h"

// Sets default values
AFRSyncObject::AFRSyncObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFRSyncObject::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AFRSyncObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

