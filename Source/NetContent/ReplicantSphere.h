// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicantSphere.generated.h"

UCLASS()
class NETCONTENT_API AReplicantSphere : public AActor
{
	GENERATED_BODY()
	
protected: 
	UPROPERTY(ReplicatedUsing= OnRep_Location, BlueprintReadWrite)
	FVector location;

public: 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool InterpolateLocation;

public:	
	// Sets default values for this actor's properties
	AReplicantSphere();

	//This method is called when Location is replicated to all the clients.
	UFUNCTION()
	void OnRep_Location();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
