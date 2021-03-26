// Fill out your copyright notice in the Description page of Project Settings.
#include "FRSyncObject.h"
#include "FRGameMode.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AFRSyncObject::AFRSyncObject(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

AFRSyncObject::AFRSyncObject(const FObjectInitializer& ObjectInitializer){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AFRSyncObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFRSyncObject, ServerStart);
}

// Called when the game starts or when spawned
void AFRSyncObject::BeginPlay(){
	Super::BeginPlay();
	
	AFRGameMode* gamemode = GetWorld()->GetAuthGameMode<AFRGameMode>();
	if(gamemode) {
		SyncObjectIndex = gamemode->SyncObjects.Add(this);
	}	
}

void AFRSyncObject::StartObject_Implementation() {
	ServerStart = true;
}

// Called every frame
void AFRSyncObject::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

