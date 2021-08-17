// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Interactable.h"
#include "RPCParticleSpawner.generated.h"

UCLASS()
class NETCONTENT_API ARPCParticleSpawner : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public: 
	//Default system to be spawned on when this actor is activated.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* DefaultSystem;

	UPROPERTY(EditAnywhere)
	uint8 bUseReliable:1;

public:	
	// Sets default values for this actor's properties
	ARPCParticleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Server Unreliable RPC
	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable)
	void SpawnUnreliable();
	void SpawnUnreliable_Implementation();

	//Server Reliable RPC
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void SpawnReliable();
	void SpawnReliable_Implementation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activation_Implementation(AController* controller) override;

};
