// Fill out your copyright notice in the Description page of Project Settings.


#include "CompressedObject.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACompressedObject::ACompressedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ACompressedObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACompressedObject::OnRep_QuantizedValue()
{
	//When the value arrives on client, update the FVector variable. You could also use the quantized Value directly in the action.
	value = quantizedValue;
}

void ACompressedObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACompressedObject, quantizedValue);
}

// Called every frame
void ACompressedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		//When object has authority, it takes a random vector.
		value = FMath::VRand();

		//And stores in a quantized-form for replication.
		quantizedValue = value;
	}
}

