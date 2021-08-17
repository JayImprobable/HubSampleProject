// Fill out your copyright notice in the Description page of Project Settings.


#include "NetClock.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ANetClock::ANetClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	if(TemplateMaterial != nullptr)
	{
		currentMaterial = UMaterialInstanceDynamic::Create(TemplateMaterial, this);
		Plane->SetMaterial(0, currentMaterial);
	}
	
}

// Called when the game starts or when spawned
void ANetClock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANetClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANetClock::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetClock, Filling);
}
