// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplicantSphere.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AReplicantSphere::AReplicantSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

// Called when the game starts or when spawned
void AReplicantSphere::BeginPlay()
{
	Super::BeginPlay();
	location = GetActorLocation();
	
}

// Called every frame
void AReplicantSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		SetActorLocation(location);
	}
	else 
	{
		if (InterpolateLocation)
		{ 
			SetActorLocation(FMath::Lerp(GetActorLocation(), location, DeltaTime * 5.0f));
		}
		else
		{
			SetActorLocation(location);
		}
	}
	
	
}

void AReplicantSphere::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AReplicantSphere, location);
}

void AReplicantSphere::OnRep_Location()
{
	//
}

