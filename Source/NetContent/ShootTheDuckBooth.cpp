// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTheDuckBooth.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AShootTheDuckBooth::AShootTheDuckBooth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

}

// Called when the game starts or when spawned
void AShootTheDuckBooth::BeginPlay()
{
	Super::BeginPlay();
	timeInternal = 0.0f;
}

void AShootTheDuckBooth::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{ 
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}

// Called every frame
void AShootTheDuckBooth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeInternal += DeltaTime;

}

