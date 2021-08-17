// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CompressedObject.generated.h"

UCLASS()
class NETCONTENT_API ACompressedObject : public AActor
{
	GENERATED_BODY()

protected: 
	UPROPERTY()
	FVector value; // 32 bits per component

	UPROPERTY(ReplicatedUsing= OnRep_QuantizedValue)
	FVector_NetQuantize quantizedValue ; //0 decimal precision, up to 20 bits per component

public:	
	// Sets default values for this actor's properties
	ACompressedObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_QuantizedValue();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
