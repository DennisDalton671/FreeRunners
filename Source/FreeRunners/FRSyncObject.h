// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRSyncObject.generated.h"

UCLASS(Abstract)
class FREERUNNERS_API AFRSyncObject : public AActor
{
	GENERATED_BODY()
	
public:	
	/** [server] starts objects that need to be synced across clients */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="FreeRunners")
	void StartObject();
	virtual void StartObject_Implementation();

	AFRSyncObject();
	AFRSyncObject(const FObjectInitializer& ObjectInitializer);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Replicated, BlueprintReadWrite, Category="FreeRunners")
	bool ServerStart{};
	int SyncObjectIndex{};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
