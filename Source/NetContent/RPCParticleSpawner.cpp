// Fill out your copyright notice in the Description page of Project Settings.


#include "RPCParticleSpawner.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARPCParticleSpawner::ARPCParticleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ARPCParticleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPCParticleSpawner::SpawnUnreliable_Implementation()
{
	if(DefaultSystem != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultSystem, GetActorTransform(), true, EPSCPoolMethod::AutoRelease);
}

void ARPCParticleSpawner::SpawnReliable_Implementation()
{
	if (DefaultSystem != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultSystem, GetActorTransform(), true, EPSCPoolMethod::AutoRelease);
}

// Called every frame
void ARPCParticleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPCParticleSpawner::Activation_Implementation(AController * controller)
{
	if (GetNetMode() == ENetMode::NM_ListenServer) 
	{
		if (bUseReliable)
			SpawnReliable();
		else
			SpawnUnreliable();
	}		
}

